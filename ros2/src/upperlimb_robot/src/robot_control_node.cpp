// Copyright 2024 Zhang Chenxu
// Licensed under the Apache License, Version 2.0

#include "rclcpp/rclcpp.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"

#include "upperlimb_robot/msg/control_command.hpp"
#include "upperlimb_robot/msg/system_state.hpp"
#include "upperlimb_robot/msg/robot_state.hpp"
#include "upperlimb_robot/msg/ssvep_result.hpp"
#include "upperlimb_robot/msg/ssvep_action_status.hpp"

#include "upperlimb_robot/gxn.h"
#include "upperlimb_robot/control_algorithms.hpp"

#include <array>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;


// ===================== GTN 底层库调用串行化 =====================
//
// Linux 版 GTN/EtherCAT 库在状态采集线程和控制线程中被同时调用时，
// 容易出现轴模式读数异常、PT 下发失败、同步失败等问题。
// 下面这些宏会把所有 GTN_* 调用统一转到 RobotControlNode::callGtn()，
// 由同一把 gtn_mutex_ 保护，保证任意时刻只有一个线程访问底层库。
//
#define GTN_Open(...) callGtn([&]() { return ::GTN_Open(__VA_ARGS__); })
#define GTN_Close(...) callGtn([&]() { return ::GTN_Close(__VA_ARGS__); })
#define GTN_LoadConfig(...) callGtn([&]() { return ::GTN_LoadConfig(__VA_ARGS__); })
#define GTN_ClrSts(...) callGtn([&]() { return ::GTN_ClrSts(__VA_ARGS__); })
#define GTN_InitEcatComm(...) callGtn([&]() { return ::GTN_InitEcatComm(__VA_ARGS__); })
#define GTN_IsEcatReady(...) callGtn([&]() { return ::GTN_IsEcatReady(__VA_ARGS__); })
#define GTN_StartEcatComm(...) callGtn([&]() { return ::GTN_StartEcatComm(__VA_ARGS__); })
#define GTN_TerminateEcatComm(...) callGtn([&]() { return ::GTN_TerminateEcatComm(__VA_ARGS__); })
#define GTN_AxisOn(...) callGtn([&]() { return ::GTN_AxisOn(__VA_ARGS__); })
#define GTN_AxisOff(...) callGtn([&]() { return ::GTN_AxisOff(__VA_ARGS__); })
#define GTN_GetSts(...) callGtn([&]() { return ::GTN_GetSts(__VA_ARGS__); })
#define GTN_GetEcatEncPos(...) callGtn([&]() { return ::GTN_GetEcatEncPos(__VA_ARGS__); })
#define GTN_SetPrfPos(...) callGtn([&]() { return ::GTN_SetPrfPos(__VA_ARGS__); })
#define GTN_SetEncPos(...) callGtn([&]() { return ::GTN_SetEncPos(__VA_ARGS__); })
#define GTN_SynchAxisPos(...) callGtn([&]() { return ::GTN_SynchAxisPos(__VA_ARGS__); })
#define GTN_GetEcatRawData(...) callGtn([&]() { return ::GTN_GetEcatRawData(__VA_ARGS__); })
#define GTN_GetEcatAxisAtlTorque(...) callGtn([&]() { return ::GTN_GetEcatAxisAtlTorque(__VA_ARGS__); })
#define GTN_GetEncVel(...) callGtn([&]() { return ::GTN_GetEncVel(__VA_ARGS__); })
#define GTN_Stop(...) callGtn([&]() { return ::GTN_Stop(__VA_ARGS__); })
#define GTN_SetEcatAxisPT(...) callGtn([&]() { return ::GTN_SetEcatAxisPT(__VA_ARGS__); })
#define GTN_SetEcatAxisMode(...) callGtn([&]() { return ::GTN_SetEcatAxisMode(__VA_ARGS__); })
#define GTN_GetEcatAxisMode(...) callGtn([&]() { return ::GTN_GetEcatAxisMode(__VA_ARGS__); })
#define GTN_PrfTrap(...) callGtn([&]() { return ::GTN_PrfTrap(__VA_ARGS__); })
#define GTN_SetTrapPrm(...) callGtn([&]() { return ::GTN_SetTrapPrm(__VA_ARGS__); })
#define GTN_SetVel(...) callGtn([&]() { return ::GTN_SetVel(__VA_ARGS__); })
#define GTN_SetPos(...) callGtn([&]() { return ::GTN_SetPos(__VA_ARGS__); })
#define GTN_Update(...) callGtn([&]() { return ::GTN_Update(__VA_ARGS__); })

class RobotControlNode : public rclcpp::Node
{
public:
  RobotControlNode() : Node("robot_control_node")
  {
    hardware_enabled_ = this->declare_parameter<bool>("hardware_enabled", true);
    serial_device_ = this->declare_parameter<std::string>(
        "ssvep.serial_device", upperlimb_robot::SSVEP_DEFAULT_SERIAL_DEVICE);
    RCLCPP_INFO(
        this->get_logger(),
        "robot_control_node 启动，hardware_enabled=%d，ssvep.serial_device=%s",
        static_cast<int>(hardware_enabled_),
        serial_device_.empty() ? "<disabled>" : serial_device_.c_str());

    control_command_sub_ =
        this->create_subscription<upperlimb_robot::msg::ControlCommand>(
            "control_command",
            10,
            std::bind(&RobotControlNode::controlCommandCallback, this, std::placeholders::_1));

    system_pub_ =
        this->create_publisher<upperlimb_robot::msg::SystemState>("system_state", 10);

    robot_state_pub_ =
        this->create_publisher<upperlimb_robot::msg::RobotState>("robot_state", 10);

    joint_state_pub_ =
        this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

    ssvep_result_pub_ =
        this->create_publisher<upperlimb_robot::msg::SsvepResult>(
            "ssvep/result", rclcpp::QoS(50).reliable().transient_local());

    ssvep_status_pub_ =
        this->create_publisher<upperlimb_robot::msg::SsvepActionStatus>("ssvep/action_status", 20);

    state_timer_ = this->create_wall_timer(
        500ms, std::bind(&RobotControlNode::publishSystemState, this));

    ssvep_status_timer_ = this->create_wall_timer(
        100ms, std::bind(&RobotControlNode::publishSsvepStatus, this));

    if (serial_device_.empty())
    {
      publishSsvepResult("", 8, "串口未配置；调试模式可正常使用");
    }

    if (!hardware_enabled_)
    {
      controller_init_ = true;
      joint_init_ = true;
      system_ready_ = true;
      {
        std::lock_guard<std::mutex> state_lock(state_mutex_);
        for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
        {
          latest_motor_state_.enable[i] = isControlledAxisIndex(i);
        }
      }
      {
        std::lock_guard<std::mutex> sensor_lock(sensor_mutex_);
        latest_sensor_state_.valid = true;
      }
      state_ready_.store(true);
      publishSystemState();
      running_.store(true);
      control_thread_ = std::thread(&RobotControlNode::controlLoop, this);
      if (!serial_device_.empty())
      {
        serial_thread_ = std::thread(&RobotControlNode::serialLoop, this);
      }
      RCLCPP_INFO(this->get_logger(), "调试启动：未调用任何 GTN/EtherCAT 接口");
      return;
    }

    if (!initController())
    {
      RCLCPP_ERROR(this->get_logger(), "控制器初始化失败");
      publishSystemState();
      return;
    }
    controller_init_ = true;
    publishSystemState();

    if (!initMotors())
    {
      RCLCPP_ERROR(this->get_logger(), "电机初始化失败");
      publishSystemState();
      return;
    }
    joint_init_ = true;

    system_ready_ = controller_init_ && joint_init_;
    publishSystemState();

    RCLCPP_INFO(this->get_logger(), "硬件初始化完成，系统准备就绪");

    running_.store(true);

    state_read_thread_ = std::thread(&RobotControlNode::stateReadLoop, this);
    RCLCPP_INFO(this->get_logger(), "状态采集线程已启动");

    control_thread_ = std::thread(&RobotControlNode::controlLoop, this);
    RCLCPP_INFO(this->get_logger(), "控制线程已启动");

    if (!serial_device_.empty())
    {
      serial_thread_ = std::thread(&RobotControlNode::serialLoop, this);
      RCLCPP_INFO(this->get_logger(), "SSVEP 串口线程已启动");
    }
  }

  ~RobotControlNode() override
  {
    shutdownHardware();
  }

  void shutdownHardware()
  {
    if (shutdown_done_)
    {
      return;
    }
    shutdown_done_ = true;

    running_.store(false);

    if (state_read_thread_.joinable())
    {
      state_read_thread_.join();
    }

    if (control_thread_.joinable())
    {
      control_thread_.join();
    }

    if (serial_thread_.joinable())
    {
      serial_thread_.join();
    }

    if (!hardware_enabled_)
    {
      fprintf(stderr, "调试模式已关闭，未访问硬件。\n");
      fflush(stderr);
      return;
    }

    fprintf(stderr, "正在安全关闭机器人系统...\n");
    fflush(stderr);

    clearAllTorqueCommands();
    restoreAllAxesToPositionMode();
    const bool axes_ok = stopAllAxesRaw();

    if (axes_ok)
    {
      fprintf(stderr, "所有电机已安全关闭。\n");
    }
    else
    {
      fprintf(stderr, "部分电机关闭失败，请检查上面的错误信息。\n");
    }
    fflush(stderr);

    if (ecat_started_)
    {
      const short rtn = GTN_TerminateEcatComm(core_id_);
      if (rtn == 0)
      {
        fprintf(stderr, "EtherCAT通信已关闭。\n");
      }
      else
      {
        fprintf(stderr, "EtherCAT通信关闭失败，错误码=%d\n", rtn);
      }
      fflush(stderr);
      ecat_started_ = false;
    }

    if (controller_opened_)
    {
      const short rtn = GTN_Close();
      if (rtn == 0)
      {
        fprintf(stderr, "控制器已关闭。\n");
      }
      else
      {
        fprintf(stderr, "控制器关闭失败，错误码=%d\n", rtn);
      }
      fflush(stderr);
      controller_opened_ = false;
    }
  }

private:
  // ===================== GTN 调用互斥封装 =====================
  //
  // 所有 GTN_* 底层库函数都通过宏转到这里。
  // 目的不是提高性能，而是先验证 Linux 版 GTN 库在多线程访问下是否会出现
  // 非法模式值、PT 失败、同步失败等异常。
  //
  template <typename Fn>
  auto callGtn(Fn &&fn) -> decltype(fn())
  {
    std::lock_guard<std::mutex> lock(gtn_mutex_);
    return fn();
  }

  // ===================== 模式进入失败回退 =====================
  //
  // onModeEnter() 内部不能直接修改 applied_mode_，但可以请求状态机回退。
  // 状态机随后会把 applied_mode_ 和 current_mode_ 统一改到 fallback_mode，
  // 防止进入失败后仍短暂执行失败模式的控制输出。
  //
  void requestModeEnterFallback(int fallback_mode)
  {
    mode_enter_failed_ = true;
    mode_enter_fallback_mode_ = fallback_mode;
  }

  // ===================== 主动控制轴过滤 =====================
  //
  // 机械结构中每条臂最后 3 个关节暂不参与控制：
  // 右臂 joint18~joint20 -> 控制层索引 7~9 / 物理轴 8~10
  // 左臂 joint8~joint10  -> 控制层索引 17~19 / 物理轴 18~20
  //
  // 当前执行层只控制 14 个主动关节：
  // 右臂 joint11~joint17 -> 控制层索引 0~6
  // 左臂 joint1~joint7   -> 控制层索引 10~16
  //
  bool isControlledAxisIndex(std::size_t i) const
  {
    return (i <= 6) || (i >= 10 && i <= 16);
  }

  // ===================== 控制命令回调 =====================
  //
  // 这里仅记录“请求模式”。
  // 真正的模式进入/退出动作统一放在控制线程里的状态机中处理，
  // 这样可以避免在 ROS 回调线程里直接改硬件状态。
  //
  void controlCommandCallback(const upperlimb_robot::msg::ControlCommand::SharedPtr msg)
  {
    if (msg->emergency_stop)
    {
      emergency_stop_requested_.store(true);
      RCLCPP_ERROR(this->get_logger(), "收到 GUI 安全停止请求");
      return;
    }

    // 精简工程只接受保留的控制模式。即使旧版 GUI 或脚本仍发送原模式号，
    // 只允许当前界面保留的七种命令进入执行路径。
    switch (msg->command)
    {
    case upperlimb_robot::MODE_IDLE:
    case upperlimb_robot::MODE_LEFT_PRESET_POSITION:
    case upperlimb_robot::MODE_RIGHT_PRESET_POSITION:
    case upperlimb_robot::MODE_ZERO_FORCE:
    case upperlimb_robot::MODE_RIGHT_ZERO_FORCE:
    case upperlimb_robot::MODE_BILATERAL_ZERO_FORCE:
    case upperlimb_robot::MODE_SSVEP:
      break;
    default:
      RCLCPP_WARN(
          this->get_logger(),
          "拒绝已移除的控制模式 command=%d",
          msg->command);
      return;
    }

    const bool previous_debug = ssvep_debug_requested_.exchange(msg->ssvep_debug);
    if (msg->command == upperlimb_robot::MODE_SSVEP &&
        previous_debug != msg->ssvep_debug)
    {
      ssvep_reconfigure_requested_.store(true);
    }

    if (msg->command == upperlimb_robot::MODE_SSVEP && msg->ssvep_debug)
    {
      pending_ssvep_target_.store(static_cast<int>(msg->ssvep_test_target));
    }
    current_mode_.store(msg->command);
    RCLCPP_INFO(
        this->get_logger(),
        "收到控制命令=%d ssvep_debug=%d test_target=%u",
        msg->command,
        static_cast<int>(msg->ssvep_debug),
        static_cast<unsigned>(msg->ssvep_test_target));
  }

  // ===================== SSVEP POSIX 串口 =====================
  // 串口线程只做读取、解析和发布，不调用 GTN，也不直接修改算法对象。
  // 有效目标通过 pending_ssvep_target_ 交给控制线程消费。
  static bool configureSsvepSerial(int fd)
  {
    static_assert(
        upperlimb_robot::SSVEP_SERIAL_BAUD == 115200,
        "新增波特率时需要在 configureSsvepSerial 中补充 termios 映射");
    termios options{};
    if (tcgetattr(fd, &options) != 0)
    {
      return false;
    }
    cfmakeraw(&options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    options.c_cflag |= CLOCAL | CREAD;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS;
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 0;
    return tcsetattr(fd, TCSANOW, &options) == 0;
  }

  void publishSsvepResult(
      const std::string &raw,
      std::uint8_t status,
      const std::string &detail,
      std::uint64_t sequence = 0,
      const std::string &source = "",
      std::uint8_t target = 0,
      double frequency_hz = 0.0)
  {
    upperlimb_robot::msg::SsvepResult message;
    message.received_at = this->now();
    message.raw = raw;
    message.status = status;
    message.detail = detail;
    message.sequence = sequence;
    message.source = source;
    message.target = target;
    message.frequency_hz = frequency_hz;
    message.serial_connected = serial_connected_.load();
    message.serial_device = serial_device_;
    message.baud_rate = upperlimb_robot::SSVEP_SERIAL_BAUD;
    ssvep_result_pub_->publish(message);
  }

  void parseSsvepFrame(const std::string &raw, std::int64_t &last_sequence)
  {
    const auto parsed = upperlimb_robot::parseSsvepProtocolFrame(raw, last_sequence);
    if (parsed.status != 0)
    {
      publishSsvepResult(
          raw, parsed.status, parsed.detail, parsed.sequence,
          parsed.source, parsed.target, parsed.frequency_hz);
      return;
    }

    const bool real_eeg_allowed =
        current_mode_.load() == upperlimb_robot::MODE_SSVEP &&
        !ssvep_debug_requested_.load() && parsed.source == "EEG";
    const std::string detail = real_eeg_allowed
        ? "协议校验通过，已交给控制线程"
        : "协议校验通过，仅发布显示（当前不是SSVEP实机模式）";
    publishSsvepResult(
        raw, 0, detail, parsed.sequence, parsed.source,
        parsed.target, parsed.frequency_hz);
    if (real_eeg_allowed)
    {
      pending_ssvep_target_.store(static_cast<int>(parsed.target));
    }
  }

  void serialLoop()
  {
    std::string buffer;
    while (running_.load())
    {
      int fd = open(serial_device_.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
      if (fd < 0 || !configureSsvepSerial(fd))
      {
        serial_connected_.store(false);
        if (fd >= 0)
        {
          close(fd);
        }
        publishSsvepResult("", 5, "串口打开/配置失败: " + std::string(std::strerror(errno)));
        std::this_thread::sleep_for(1s);
        continue;
      }

      serial_connected_.store(true);
      RCLCPP_INFO(this->get_logger(), "SSVEP 串口已连接: %s", serial_device_.c_str());
      publishSsvepResult("", 7, "串口已连接");
      buffer.clear();
      std::int64_t last_sequence = -1;
      bool reconnect = false;
      while (running_.load() && !reconnect)
      {
        char bytes[256];
        const ssize_t count = read(fd, bytes, sizeof(bytes));
        if (count < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
          serial_connected_.store(false);
          publishSsvepResult("", 5, "串口读取失败: " + std::string(std::strerror(errno)));
          reconnect = true;
          continue;
        }
        if (count > 0)
        {
          buffer.append(bytes, static_cast<std::size_t>(count));
          if (buffer.size() > upperlimb_robot::SSVEP_MAX_FRAME_BYTES &&
              buffer.find("\r\n") == std::string::npos)
          {
            publishSsvepResult(buffer, 4, "未结束数据超过最大长度，已丢弃");
            buffer.clear();
          }
          for (;;)
          {
            const std::size_t end = buffer.find("\r\n");
            if (end == std::string::npos)
            {
              break;
            }
            const std::string frame = buffer.substr(0, end);
            buffer.erase(0, end + 2);
            if (frame.size() > upperlimb_robot::SSVEP_MAX_FRAME_BYTES)
            {
              publishSsvepResult(frame, 4, "完整帧超过最大长度");
            }
            else
            {
              parseSsvepFrame(frame, last_sequence);
            }
          }
        }
        std::this_thread::sleep_for(10ms);
      }
      close(fd);
      serial_connected_.store(false);
    }
  }

  // ===================== 模式状态机更新 =====================
  //
  // current_mode_ : 外部请求的新模式
  // applied_mode_ : 已经完成进入动作的当前模式
  //
  // 每轮控制循环开始时调用一次：
  // 1. 如果模式没变，直接返回
  // 2. 先执行旧模式退出动作
  // 3. 再执行新模式进入动作
  // 4. 最后更新 applied_mode_
  //
  void updateModeStateMachine()
  {
    const int requested_mode = current_mode_.load();

    if (requested_mode == applied_mode_)
    {
      return;
    }

    const int old_mode = applied_mode_;

    onModeExit(old_mode, requested_mode);

    // onModeEnter() 可能因为轴模式切换失败而要求回退。
    // 进入失败时不能把 applied_mode_ 仍然设置成 requested_mode，
    // 否则控制循环会短暂以失败模式继续计算/下发，造成一帧错误 PT。
    mode_enter_failed_ = false;
    mode_enter_fallback_mode_ = requested_mode;

    onModeEnter(old_mode, requested_mode);

    if (mode_enter_failed_)
    {
      applied_mode_ = mode_enter_fallback_mode_;
      current_mode_.store(mode_enter_fallback_mode_);

      RCLCPP_WARN(
          this->get_logger(),
          "模式进入失败: old=%d requested=%d fallback=%d",
          old_mode,
          requested_mode,
          mode_enter_fallback_mode_);
      return;
    }

    applied_mode_ = requested_mode;

    RCLCPP_INFO(
        this->get_logger(),
        "模式切换完成: old=%d -> new=%d",
        old_mode,
        requested_mode);
  }

  // ===================== 模式退出动作 =====================
  //
  // 设计目的：
  // 1. 退出扭矩相关模式时，先清零 PT，再恢复到位置模式
  // 2. 退出预设位置模式时，停止当前残余位置运动，并清除位置命令缓存
  // 3. 下一次进入预设位置模式时，保证位置命令和 Trap 参数会重新完整下发
  //
  void onModeExit(int old_mode, int new_mode)
  {
    (void)new_mode;

    if (!hardware_enabled_)
    {
      return;
    }

    switch (old_mode)
    {

    // 清零扭矩命令，再恢复位置模式
    case upperlimb_robot::MODE_ZERO_FORCE:
    case upperlimb_robot::MODE_RIGHT_ZERO_FORCE:
    case upperlimb_robot::MODE_BILATERAL_ZERO_FORCE:
    case upperlimb_robot::MODE_SSVEP:
      clearAllTorqueCommands();
      stopAllAxesMotionOnly();
      restoreAllAxesToPositionMode();
      invalidateAllPositionCommandCache();
      break;

    // 停止当前残余位置运动，并清除位置命令缓存
    case upperlimb_robot::MODE_LEFT_PRESET_POSITION:
    case upperlimb_robot::MODE_RIGHT_PRESET_POSITION:
      stopAllAxesMotionOnly();
      invalidateAllPositionCommandCache();
      break;

    case upperlimb_robot::MODE_IDLE:

    default:
      break;
    }
  }

  // ===================== 模式进入动作 =====================
  //
  // 进入零力模式时，只有在传感器数据有效时才允许记录零偏。
  //
  void onModeEnter(int old_mode, int new_mode)
  {
    // 只要是从 Idle 进入其他模式，就先重新使能
    if (hardware_enabled_ && old_mode == upperlimb_robot::MODE_IDLE &&
        new_mode != upperlimb_robot::MODE_IDLE)
    {
      for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
      {
        if (!isControlledAxisIndex(i))
        {
          axis_enabled_[i] = false;
          continue;
        }

        const short axis = axis_ids_[i];
        const short rtn = GTN_AxisOn(core_id_, axis);

        if (rtn != 0)
        {
          RCLCPP_ERROR(
              this->get_logger(),
              "GTN_AxisOn 失败，axis=%d，错误码=%d",
              axis,
              rtn);
        }
        else
        {
          axis_enabled_[i] = true;
        }
      }

      RCLCPP_INFO(this->get_logger(), "退出空闲模式：已重新使能 14 个主动轴，末端 6 个关节不参与控制");
    }

    if (!hardware_enabled_ && new_mode != upperlimb_robot::MODE_SSVEP)
    {
      RCLCPP_INFO(this->get_logger(), "调试启动：模式%d仅使用内部模拟，不执行硬件进入动作", new_mode);
      return;
    }

    switch (new_mode)
    {
    case upperlimb_robot::MODE_SSVEP:
    {
      ssvep_fault_safe_done_ = false;
      const bool debug_mode = ssvep_debug_requested_.load() || !hardware_enabled_;
      {
        std::lock_guard<std::mutex> lock(ssvep_mutex_);
        ssvep_control_.reset(debug_mode);
      }
      pending_ssvep_target_.store(-1);

      if (debug_mode)
      {
        {
          std::lock_guard<std::mutex> lock(state_mutex_);
          ssvep_simulated_state_ = latest_motor_state_;
        }
        RCLCPP_INFO(this->get_logger(), "进入 SSVEP 调试模式：不向 EtherCAT 下发 SSVEP 控制命令");
        break;
      }

      // 从任一零力模式进入时沿用已有六维力零偏，避免患者施力时重新校零。
      const bool came_from_zero_force =
          old_mode == upperlimb_robot::MODE_ZERO_FORCE ||
          old_mode == upperlimb_robot::MODE_RIGHT_ZERO_FORCE ||
          old_mode == upperlimb_robot::MODE_BILATERAL_ZERO_FORCE;
      const bool bias_ok = came_from_zero_force ? true : captureForceSensorBias();
      const bool torque_ok = enterDualArmTorqueModeOnce();
      if (!bias_ok || !torque_ok)
      {
        RCLCPP_ERROR(
            this->get_logger(),
            "进入 SSVEP 实机模式失败：bias_ok=%d torque_ok=%d",
            static_cast<int>(bias_ok), static_cast<int>(torque_ok));
        requestModeEnterFallback(upperlimb_robot::MODE_IDLE);
      }
      break;
    }
    case upperlimb_robot::MODE_ZERO_FORCE:
    {
      const bool ok = captureForceSensorBias();
      if (ok)
      {
        RCLCPP_INFO(this->get_logger(), "进入零力模式，已记录六维力零偏");
      }
      else
      {
        RCLCPP_WARN(this->get_logger(), "进入零力模式失败：当前传感器数据无效，未记录零偏");
      }
      break;
    }
    case upperlimb_robot::MODE_RIGHT_ZERO_FORCE:
    {
      const bool ok = captureForceSensorBias();
      if (ok)
      {
        RCLCPP_INFO(this->get_logger(), "进入右臂零力模式，已记录六维力零偏");
      }
      else
      {
        RCLCPP_WARN(this->get_logger(), "进入右臂零力模式失败：当前传感器数据无效，未记录零偏");
      }
      break;
    }

    case upperlimb_robot::MODE_BILATERAL_ZERO_FORCE:
    {
      const bool bias_ok = captureForceSensorBias();
      const bool torque_ok = enterDualArmTorqueModeOnce();

      if (bias_ok && torque_ok)
      {
        RCLCPP_INFO(this->get_logger(), "进入双臂零力模式：已记录六维力零偏，14 个主动轴已一次性切到扭矩模式");
      }
      else
      {
        RCLCPP_WARN(
            this->get_logger(),
            "进入双臂零力模式失败：bias_ok=%d, torque_ok=%d；退回 Idle，避免控制循环内反复切轴模式",
            static_cast<int>(bias_ok),
            static_cast<int>(torque_ok));

        clearDualArmTorqueCommandsNoModeSwitch();
        stopAllAxesMotionOnly();
        restoreAllAxesToPositionMode();
        requestModeEnterFallback(upperlimb_robot::MODE_IDLE);
      }
      break;
    }

    case upperlimb_robot::MODE_LEFT_PRESET_POSITION:
    {
      RCLCPP_INFO(this->get_logger(), "进入左臂预设位置模式");
      break;
    }

    case upperlimb_robot::MODE_RIGHT_PRESET_POSITION:
    {
      RCLCPP_INFO(this->get_logger(), "进入右臂预设位置模式");
      break;
    }

    case upperlimb_robot::MODE_IDLE:
    {
      // // 先清掉可能残留的扭矩命令
      // clearAllTorqueCommands();

      // // 尽量先切回位置模式，避免驱动还停留在扭矩模式
      // restoreAllAxesToPositionMode();

      // // 停止所有轴当前运动
      // stopAllAxesMotionOnly();

      // // 关闭所有轴使能
      // for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
      // {
      //   const short axis = axis_ids_[i];
      //   const short rtn = GTN_AxisOff(core_id_, axis);

      //   if (rtn != 0)
      //   {
      //     RCLCPP_ERROR(
      //         this->get_logger(),
      //         "GTN_AxisOff 失败，axis=%d，错误码=%d",
      //         axis,
      //         rtn);
      //   }

      //   axis_in_torque_mode_[i] = false;
      // }

      // RCLCPP_INFO(this->get_logger(), "进入空闲模式");
      // break;
    }

    default:
      break;
    }
  }

  // ===================== 双臂扭矩模式辅助函数 =====================
  //
  // 双臂零力模式同时控制 14 个主动关节，不应在控制循环内反复执行
  // “位置模式 <-> 扭矩模式”切换。
  //
  // 策略：
  // 1. 进入模式时一次性切 14 个主动轴到扭矩模式。
  // 2. 控制循环中只发送 PT 扭矩。
  // 3. 算法本轮无效时，只清零 PT，不立刻切回位置模式。
  // 4. 退出模式时再统一恢复位置模式。
  //
  bool isDualArmTorqueMode(int mode) const
  {
    return mode == upperlimb_robot::MODE_BILATERAL_ZERO_FORCE;
  }

  std::array<std::size_t, 14> dualArmActiveTorqueIndices() const
  {
    return {
        // 右臂 joint11~joint17 -> 控制层索引 0~6
        0, 1, 2, 3, 4, 5, 6,
        // 左臂 joint1~joint7 -> 控制层索引 10~16
        10, 11, 12, 13, 14, 15, 16};
  }

  bool enterDualArmTorqueModeOnce()
  {
    bool all_ok = true;

    for (const std::size_t i : dualArmActiveTorqueIndices())
    {
      if (i >= upperlimb_robot::AXIS_NUM)
      {
        all_ok = false;
        continue;
      }

      if (!ensureAxisInTorqueMode(i))
      {
        all_ok = false;
        continue;
      }

      last_target_torque_[i] = 0.0;
      command_sent_[i] = false;
      position_profile_configured_[i] = false;
    }

    return all_ok;
  }

  void clearDualArmTorqueCommandsNoModeSwitch()
  {
    for (const std::size_t i : dualArmActiveTorqueIndices())
    {
      if (i >= upperlimb_robot::AXIS_NUM)
      {
        continue;
      }

      const int axis = axis_ids_[i];
      const short rtn = GTN_SetEcatAxisPT(core_id_, axis, 0);
      if (rtn != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "双臂扭矩模式清零 PT 失败，轴%d，错误码=%d", axis, rtn);
      }

      last_target_torque_[i] = 0.0;
    }
  }

  // ===================== 控制器初始化 =====================
  bool initController()
  {
    short rtn = GTN_Open();
    if (rtn != 0)
    {
      RCLCPP_ERROR(this->get_logger(), "GTN_Open 打开控制器失败，错误码=%d", rtn);
      return false;
    }
    controller_opened_ = true;
    RCLCPP_INFO(this->get_logger(), "GTN_Open 成功");

    std::string config_path;
    try
    {
      const std::string pkg_share =
          ament_index_cpp::get_package_share_directory("upperlimb_robot");
      config_path = pkg_share + "/config/Gecat.eni";
    }
    catch (const std::exception &e)
    {
      RCLCPP_ERROR(this->get_logger(), "获取包配置目录失败: %s", e.what());
      return false;
    }

    rtn = GTN_LoadConfig(core_id_, const_cast<char *>(config_path.c_str()));
    if (rtn != 0)
    {
      RCLCPP_ERROR(
          this->get_logger(),
          "GTN_LoadConfig 加载配置文件失败，错误码=%d, 路径=%s",
          rtn, config_path.c_str());
      return false;
    }
    RCLCPP_INFO(this->get_logger(), "GTN_LoadConfig 成功");

    rtn = GTN_ClrSts(core_id_, 1, static_cast<short>(upperlimb_robot::AXIS_NUM));
    if (rtn != 0)
    {
      RCLCPP_WARN(this->get_logger(), "GTN_ClrSts 更新配置状态失败，错误码=%d", rtn);
    }

    rtn = GTN_InitEcatComm(core_id_);
    if (rtn != 0)
    {
      RCLCPP_ERROR(this->get_logger(), "EtherCAT初始化失败，错误码=%d", rtn);
      return false;
    }

    short ready = 0;
    int retry = 0;
    constexpr int max_retry = 100;

    do
    {
      rtn = GTN_IsEcatReady(core_id_, &ready);
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "检测EtherCAT状态失败，错误码=%d", rtn);
        return false;
      }

      if (ready == 1)
      {
        break;
      }

      rclcpp::sleep_for(50ms);
      retry++;
    } while (retry < max_retry);

    if (ready != 1)
    {
      RCLCPP_ERROR(this->get_logger(), "EtherCAT启动超时");
      return false;
    }

    rtn = GTN_StartEcatComm(core_id_);
    if (rtn != 0)
    {
      RCLCPP_ERROR(this->get_logger(), "启动EtherCAT通信失败，错误码=%d", rtn);
      return false;
    }

    ecat_started_ = true;
    RCLCPP_INFO(this->get_logger(), "EtherCAT通信启动成功");

    return true;
  }

  // ===================== 电机初始化 =====================
  bool initMotors()
  {
    short rtn = 0;

    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      const int axis = axis_ids_[i];

      if (!isControlledAxisIndex(i))
      {
        enc_pos_[i] = 0;
        axis_enabled_[i] = false;
        RCLCPP_INFO(
            this->get_logger(),
            "轴%d 为末端非控制关节，初始化阶段跳过使能、同步和模式控制",
            axis);
        continue;
      }

      rtn = GTN_GetEcatEncPos(core_id_, axis, &enc_pos_[i]);
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "读取轴%d编码器位置失败，错误码=%d", axis, rtn);
        return false;
      }

      rtn = GTN_SetPrfPos(core_id_, axis, enc_pos_[i]);
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "设置轴%d规划位置失败，错误码=%d", axis, rtn);
        return false;
      }

      rtn = GTN_SetEncPos(core_id_, axis, enc_pos_[i]);
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "设置轴%d编码器位置失败，错误码=%d", axis, rtn);
        return false;
      }

      // ===================== 同步 axis / profile / encoder =====================
      rtn = GTN_SynchAxisPos(core_id_, static_cast<long>(1L << (axis - 1)));
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "同步轴%d位置失败，错误码=%d", axis, rtn);
        return false;
      }

      rtn = GTN_AxisOn(core_id_, axis);
      if (rtn != 0)
      {
        RCLCPP_ERROR(this->get_logger(), "轴%d使能失败，错误码=%d", axis, rtn);
        return false;
      }

      axis_enabled_[i] = true;

      RCLCPP_INFO(this->get_logger(), "轴%d初始化完成，编码器位置=%d", axis, enc_pos_[i]);
    }

    return true;
  }

  // ===================== 系统状态发布 =====================
  void publishSystemState()
  {
    upperlimb_robot::msg::SystemState msg;
    msg.joint_init = joint_init_;
    msg.controller_init = controller_init_;
    msg.system_ready = system_ready_;
    system_pub_->publish(msg);
  }

  void publishSsvepStatus()
  {
    std::lock_guard<std::mutex> lock(ssvep_mutex_);
    const auto &status = ssvep_control_.status();
    upperlimb_robot::msg::SsvepActionStatus message;
    message.stamp = this->now();
    message.phase = static_cast<std::uint8_t>(status.phase);
    message.target = status.target;
    message.ready_for_command = status.ready_for_command;
    message.debug_mode = status.debug_mode;
    message.detail = status.detail;
    message.q0_deg.assign(status.q0_deg.begin(), status.q0_deg.end());
    message.target_deg.assign(status.target_deg.begin(), status.target_deg.end());
    message.actual_deg.assign(status.actual_deg.begin(), status.actual_deg.end());
    ssvep_status_pub_->publish(message);
  }

  // ===================== 读取 EtherCAT 原始 float 数据 =====================
  bool readFloatRawData(int offset, double &value)
  {
    int raw = 0;
    const short rtn =
        GTN_GetEcatRawData(core_id_, offset, 4, reinterpret_cast<unsigned char *>(&raw));

    if (rtn != 0)
    {
      value = 0.0;
      return false;
    }

    float temp = 0.0f;
    std::memcpy(&temp, &raw, sizeof(float));
    value = static_cast<double>(temp);
    return true;
  }

  // ===================== 读取单个六维力传感器 =====================
  bool readSingleForceSensor(int base_offset, upperlimb_robot::ForceSensorData &data)
  {
    bool ok = true;

    ok &= readFloatRawData(base_offset + 0, data.fx);
    ok &= readFloatRawData(base_offset + 4, data.fy);
    ok &= readFloatRawData(base_offset + 8, data.fz);
    ok &= readFloatRawData(base_offset + 12, data.mx);
    ok &= readFloatRawData(base_offset + 16, data.my);
    ok &= readFloatRawData(base_offset + 20, data.mz);

    return ok;
  }

  // ===================== 读取全部四个六维力传感器 =====================
  bool readAllForceSensors(upperlimb_robot::SensorStateCache &sensor_state)
  {
    bool ok = true;

    ok &= readSingleForceSensor(8, sensor_state.sensor[upperlimb_robot::SENSOR_RIGHT_HAND]);
    ok &= readSingleForceSensor(40, sensor_state.sensor[upperlimb_robot::SENSOR_RIGHT_ARM]);
    ok &= readSingleForceSensor(72, sensor_state.sensor[upperlimb_robot::SENSOR_LEFT_HAND]);
    ok &= readSingleForceSensor(104, sensor_state.sensor[upperlimb_robot::SENSOR_LEFT_ARM]);

    sensor_state.valid = ok;
    return ok;
  }

  // ===================== 记录当前传感器零偏 =====================
  //
  // 只有在 latest_sensor_state_.valid == true 时，才允许记录零偏。
  // 这样可以避免把未初始化值、读失败值或脏值写进 bias。
  //
  bool captureForceSensorBias()
  {
    std::lock_guard<std::mutex> lock(sensor_mutex_);

    if (!latest_sensor_state_.valid)
    {
      return false;
    }

    latest_sensor_state_.bias = latest_sensor_state_.sensor;
    return true;
  }

  // ===================== 六维力去偏 =====================
  upperlimb_robot::ForceSensorData subtractBias(
      const upperlimb_robot::ForceSensorData &raw,
      const upperlimb_robot::ForceSensorData &bias) const
  {
    upperlimb_robot::ForceSensorData out;
    out.fx = raw.fx - bias.fx;
    out.fy = raw.fy - bias.fy;
    out.fz = raw.fz - bias.fz;
    out.mx = raw.mx - bias.mx;
    out.my = raw.my - bias.my;
    out.mz = raw.mz - bias.mz;
    return out;
  }

  // ===================== 传感器状态转成数组 =====================
  // 固定 24 维，对应四个六维力传感器。
  std::vector<double> buildForceSensorArray(
      const upperlimb_robot::SensorStateCache &sensor_state) const
  {
    std::vector<double> out;
    out.reserve(24);

    const auto right_hand = subtractBias(
        sensor_state.sensor[upperlimb_robot::SENSOR_RIGHT_HAND],
        sensor_state.bias[upperlimb_robot::SENSOR_RIGHT_HAND]);

    const auto right_arm = subtractBias(
        sensor_state.sensor[upperlimb_robot::SENSOR_RIGHT_ARM],
        sensor_state.bias[upperlimb_robot::SENSOR_RIGHT_ARM]);

    const auto left_hand = subtractBias(
        sensor_state.sensor[upperlimb_robot::SENSOR_LEFT_HAND],
        sensor_state.bias[upperlimb_robot::SENSOR_LEFT_HAND]);

    const auto left_arm = subtractBias(
        sensor_state.sensor[upperlimb_robot::SENSOR_LEFT_ARM],
        sensor_state.bias[upperlimb_robot::SENSOR_LEFT_ARM]);

    auto fill_one = [&](const upperlimb_robot::ForceSensorData &s)
    {
      out.push_back(s.fx);
      out.push_back(s.fy);
      out.push_back(s.fz);
      out.push_back(s.mx);
      out.push_back(s.my);
      out.push_back(s.mz);
    };

    fill_one(right_hand);
    fill_one(right_arm);
    fill_one(left_hand);
    fill_one(left_arm);

    return out;
  }

  // ===================== 发布 RobotState =====================
  void publishRobotState(
      const upperlimb_robot::MotorStateCache &state,
      const upperlimb_robot::SensorStateCache &sensor_state)
  {
    upperlimb_robot::msg::RobotState msg;

    msg.position.assign(state.position.begin(), state.position.end());
    msg.velocity.assign(state.velocity.begin(), state.velocity.end());
    msg.torque.assign(state.torque.begin(), state.torque.end());
    msg.enabled.assign(state.enable.begin(), state.enable.end());

    const auto force_array = buildForceSensorArray(sensor_state);
    msg.force_sensor.assign(force_array.begin(), force_array.end());

    robot_state_pub_->publish(msg);
    joint_state_pub_->publish(convertToJointStateMsg(state));
  }

  // ===================== 状态采集线程 =====================
  void stateReadLoop()
  {
    std::uint64_t timeout_count = 0;

    while (running_.load())
    {
      const int state_hz = state_hz_.load();

      if (state_hz <= 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "state_hz 非法=%d，必须大于 0", state_hz);

        std::this_thread::sleep_for(100ms);
        continue;
      }

      const auto period = std::chrono::microseconds(1000000 / state_hz);
      auto cycle_start = std::chrono::steady_clock::now();

      upperlimb_robot::MotorStateCache local_state;
      upperlimb_robot::SensorStateCache local_sensor_state;

      const bool do_read_status =
          (++status_read_divider_count_ >= status_read_divider_);

      if (do_read_status)
      {
        status_read_divider_count_ = 0;
      }

      for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
      {
        const int axis = axis_ids_[i];

        if (!isControlledAxisIndex(i))
        {
          local_state.enable[i] = false;
          local_state.position[i] = 0.0;
          local_state.velocity[i] = 0.0;
          local_state.torque[i] = 0.0;
          continue;
        }

        short rtn = 0;
        int32_t sts = 0;
        int32_t enc_pos = 0;
        double vel = 0.0;
        short torque_raw = 0;

        if (do_read_status)
        {
          rtn = GTN_GetSts(core_id_, axis, &sts, 1);
          if (rtn == 0)
          {
            local_state.enable[i] = (sts != 0);
          }
          else
          {
            local_state.enable[i] = axis_enabled_[i];
          }
        }
        else
        {
          local_state.enable[i] = axis_enabled_[i];
        }

        rtn = GTN_GetEcatEncPos(core_id_, axis, &enc_pos);
        if (rtn == 0)
        {
          local_state.position[i] =
              upperlimb_robot::pulseToJointDeg(axis, static_cast<double>(enc_pos));
        }
        else
        {
          local_state.position[i] = 0.0;
        }

        rtn = GTN_GetEcatAxisAtlTorque(core_id_, axis, &torque_raw);
        if (rtn == 0)
        {
          local_state.torque[i] =
              upperlimb_robot::torqueRawToNm(axis, static_cast<double>(torque_raw));
        }
        else
        {
          local_state.torque[i] = 0.0;
        }

        rtn = GTN_GetEncVel(core_id_, axis, &vel, 1);
        if (rtn == 0)
        {
          local_state.velocity[i] =
              upperlimb_robot::pulsePerMsToJointDegPerSec(axis, vel);
        }
        else
        {
          local_state.velocity[i] = 0.0;
        }
      }

      {
        std::lock_guard<std::mutex> lock(sensor_mutex_);
        local_sensor_state.bias = latest_sensor_state_.bias;
      }

      readAllForceSensors(local_sensor_state);

      {
        std::lock_guard<std::mutex> lock(state_mutex_);
        latest_motor_state_ = local_state;
        state_ready_.store(true);
      }

      {
        std::lock_guard<std::mutex> lock(sensor_mutex_);
        latest_sensor_state_.sensor = local_sensor_state.sensor;
        latest_sensor_state_.bias = local_sensor_state.bias;
        latest_sensor_state_.valid = local_sensor_state.valid;
      }

      publish_divider_count_++;
      if (publish_divider_count_ >= publish_divider_)
      {
        publish_divider_count_ = 0;
        publishRobotState(local_state, local_sensor_state);
      }

      auto cycle_end = std::chrono::steady_clock::now();
      auto elapsed =
          std::chrono::duration_cast<std::chrono::microseconds>(cycle_end - cycle_start);

      if (elapsed < period)
      {
        std::this_thread::sleep_for(period - elapsed);
      }
      else
      {
        timeout_count++;

        if (timeout_count % 100 == 0)
        {
          double actual_hz = 1000000.0 / static_cast<double>(elapsed.count());

          RCLCPP_WARN(
              this->get_logger(),
              "状态采集循环超时，目标频率=%d Hz，实际频率=%.1f Hz，耗时=%ld us",
              state_hz_.load(),
              actual_hz,
              elapsed.count());
        }
      }
    }
  }

  void applySimulatedOutput(
      const upperlimb_robot::ControlOutputCache &output,
      double dt_s,
      bool ssvep_only)
  {
    upperlimb_robot::MotorStateCache state;
    if (ssvep_only)
    {
      state = ssvep_simulated_state_;
    }
    else
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      state = latest_motor_state_;
    }

    const double dt = std::clamp(dt_s, 0.0001, 0.1);
    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      const double old_position = state.position[i];
      if (output.use_position[i])
      {
        const double max_step = std::max(0.1, output.target_velocity[i]) * dt;
        const double error = output.target_position[i] - old_position;
        state.position[i] += std::clamp(error, -max_step, max_step);
      }
      state.velocity[i] = (state.position[i] - old_position) / dt;
      state.torque[i] = output.use_torque[i] ? output.target_torque[i] : 0.0;
      state.enable[i] = isControlledAxisIndex(i);
    }

    if (ssvep_only)
    {
      ssvep_simulated_state_ = state;
    }
    else
    {
      std::lock_guard<std::mutex> lock(state_mutex_);
      latest_motor_state_ = state;
    }

    upperlimb_robot::SensorStateCache sensor;
    {
      std::lock_guard<std::mutex> lock(sensor_mutex_);
      sensor = latest_sensor_state_;
    }
    if (++simulation_publish_count_ >= 5)
    {
      simulation_publish_count_ = 0;
      publishRobotState(state, sensor);
    }
  }

  // ===================== 控制线程 =====================
  void controlLoop()
  {
    std::uint64_t timeout_count = 0;

    while (running_.load())
    {
      const int control_hz = control_hz_.load();
      if (control_hz <= 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "control_hz 非法=%d，必须大于 0", control_hz);
        std::this_thread::sleep_for(100ms);
        continue;
      }

      const auto period = std::chrono::microseconds(1000000 / control_hz);
      auto cycle_start = std::chrono::steady_clock::now();

      if (!system_ready_)
      {
        std::this_thread::sleep_for(period);
        continue;
      }

      if (!state_ready_.load())
      {
        std::this_thread::sleep_for(period);
        continue;
      }

      upperlimb_robot::MotorStateCache local_state;
      upperlimb_robot::SensorStateCache local_sensor_state;

      {
        std::lock_guard<std::mutex> lock(state_mutex_);
        local_state = latest_motor_state_;
      }

      {
        std::lock_guard<std::mutex> lock(sensor_mutex_);
        local_sensor_state = latest_sensor_state_;
      }

      updateModeStateMachine();

      const int mode = applied_mode_;

      if (emergency_stop_requested_.exchange(false))
      {
        if (mode == upperlimb_robot::MODE_SSVEP)
        {
          std::lock_guard<std::mutex> lock(ssvep_mutex_);
          ssvep_control_.emergencyStop("GUI安全停止");
        }
        if (hardware_enabled_)
        {
          clearAllTorqueCommands();
          stopAllAxesMotionOnly();
          restoreAllAxesToPositionMode();
          ssvep_fault_safe_done_ = true;
        }
        if (mode != upperlimb_robot::MODE_SSVEP)
        {
          current_mode_.store(upperlimb_robot::MODE_IDLE);
        }
      }

      if (mode == upperlimb_robot::MODE_SSVEP &&
          ssvep_reconfigure_requested_.exchange(false))
      {
        bool can_switch = false;
        bool previous_debug = true;
        {
          std::lock_guard<std::mutex> lock(ssvep_mutex_);
          const auto status = ssvep_control_.status();
          can_switch = status.phase == upperlimb_robot::SsvepPhase::Ready;
          previous_debug = status.debug_mode;
        }
        if (can_switch)
        {
          onModeExit(mode, mode);
          onModeEnter(mode, mode);
        }
        else
        {
          ssvep_debug_requested_.store(previous_debug);
          RCLCPP_WARN(this->get_logger(), "SSVEP动作进行中，拒绝实机/调试切换");
        }
      }

      bool ssvep_debug_output = false;
      if (mode == upperlimb_robot::MODE_SSVEP)
      {
        {
          std::lock_guard<std::mutex> lock(ssvep_mutex_);
          ssvep_debug_output = ssvep_control_.status().debug_mode;
        }
        if (ssvep_debug_output)
        {
          local_state = ssvep_simulated_state_;
        }

        const int requested_target = pending_ssvep_target_.exchange(-1);
        if (requested_target >= 0)
        {
          std::string reason;
          bool accepted = false;
          {
            std::lock_guard<std::mutex> lock(ssvep_mutex_);
            accepted = ssvep_control_.requestTarget(
                static_cast<std::uint8_t>(requested_target), local_state, reason);
          }
          if (!accepted && requested_target != 0)
          {
            publishSsvepResult("", 6, reason, 0,
                               ssvep_debug_output ? "TEST" : "EEG",
                               static_cast<std::uint8_t>(requested_target), 0.0);
          }
        }
      }

      double actual_dt_s = 1.0 / static_cast<double>(control_hz);
      if (last_control_time_valid_)
      {
        actual_dt_s =
            std::chrono::duration<double>(cycle_start - last_control_time_).count();
      }
      last_control_time_ = cycle_start;
      last_control_time_valid_ = true;

      upperlimb_robot::ControlOutputCache output =
          computeControlOutput(mode, local_state, local_sensor_state, actual_dt_s);

      if (output.valid)
      {
        if (!hardware_enabled_ || ssvep_debug_output)
        {
          // SSVEP 调试始终更新独立的模拟反馈；hardware_enabled=false 时也一样。
          // 之前把该条件写成 hardware_enabled && ssvep_debug_output，导致无硬件
          // 调试时算法读取的模拟状态始终不变，最终错误进入去程超时。
          applySimulatedOutput(output, actual_dt_s, ssvep_debug_output);
        }
        else
        {
          applyControlOutput(output);
        }
      }
      else
      {
        if (!hardware_enabled_ || ssvep_debug_output)
        {
          applySimulatedOutput(output, actual_dt_s, ssvep_debug_output);
        }
        else
        {
          if (applied_mode_ == upperlimb_robot::MODE_SSVEP)
          {
            // SSVEP 故障只执行一次停止和模式恢复，避免控制周期内反复切换驱动模式。
            if (!ssvep_fault_safe_done_)
            {
              clearAllTorqueCommands();
              stopAllAxesMotionOnly();
              restoreAllAxesToPositionMode();
              ssvep_fault_safe_done_ = true;
            }
          }
          else if (isDualArmTorqueMode(applied_mode_))
          {
            // 纯14轴扭矩模式单帧无效时只清零PT，避免循环中反复切轴模式。
            clearDualArmTorqueCommandsNoModeSwitch();
          }
          else
          {
            clearAllTorqueCommands();
            restoreAllAxesToPositionMode();
          }
        }
      }

      auto cycle_end = std::chrono::steady_clock::now();
      auto elapsed =
          std::chrono::duration_cast<std::chrono::microseconds>(cycle_end - cycle_start);

      if (elapsed < period)
      {
        std::this_thread::sleep_for(period - elapsed);
      }
      else
      {
        timeout_count++;
        if (timeout_count % 100 == 0)
        {
          double actual_hz = 1000000.0 / static_cast<double>(elapsed.count());

          RCLCPP_WARN(
              this->get_logger(),
              "控制循环超时，目标频率=%d Hz，实际频率=%.1f Hz，耗时=%ld us",
              control_hz_.load(),
              actual_hz,
              elapsed.count());
        }
      }
    }
  }

  // ===================== 控制算法总入口 =====================
  upperlimb_robot::ControlOutputCache computeControlOutput(
      int mode,
      const upperlimb_robot::MotorStateCache &state,
      const upperlimb_robot::SensorStateCache &sensor_state,
      double actual_dt_s)
  {
    upperlimb_robot::ControlOutputCache output{};

    switch (mode)
    {
      // 左臂预设位置模式
    case upperlimb_robot::MODE_LEFT_PRESET_POSITION:
      upperlimb_robot::runLeftPresetPosition(state, output);
      break;
      // 右臂预设位置模式
    case upperlimb_robot::MODE_RIGHT_PRESET_POSITION:
      upperlimb_robot::runRightPresetPosition(state, output);
      break;
      // 左臂零力模式
    case upperlimb_robot::MODE_ZERO_FORCE:
      upperlimb_robot::runZeroForceMode(state, sensor_state, output);
      break;
      // 右臂零力模式
    case upperlimb_robot::MODE_RIGHT_ZERO_FORCE:
      upperlimb_robot::runRightZeroForceMode(state, sensor_state, output);
      break;
      // 双臂零力模式
    case upperlimb_robot::MODE_BILATERAL_ZERO_FORCE:
      upperlimb_robot::runBilateralZeroForceMode(state, sensor_state, output);
      break;
    case upperlimb_robot::MODE_SSVEP:
    {
      std::lock_guard<std::mutex> lock(ssvep_mutex_);
      ssvep_control_.run(state, sensor_state, actual_dt_s, output);
      break;
    }
    case upperlimb_robot::MODE_IDLE:
    default:
      upperlimb_robot::runIdle(state, output);
      break;
    }

    // ===================== 不可控末端关节输出清理 =====================
    //
    // 无论上层哪个算法写入了什么内容，控制总入口返回前都再次清除：
    // 右臂最后三个关节 -> 控制层索引 7~9
    // 左臂最后三个关节 -> 控制层索引 17~19
    //
    // applyPositionOutput()/applyTorqueOutput() 还会通过 isControlledAxisIndex()
    // 再过滤一次，因此算法层和执行层形成双重保护。
    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (isControlledAxisIndex(i))
      {
        continue;
      }

      output.use_position[i] = false;
      output.use_velocity[i] = false;
      output.use_torque[i] = false;

      output.target_position[i] = 0.0;
      output.target_velocity[i] = 0.0;
      output.target_torque[i] = 0.0;
      output.target_acc[i] = 0.0;
      output.target_dec[i] = 0.0;
      output.target_smooth_time[i] = 0;
    }

    return output;
  }

  // ===================== 执行控制输出 =====================
  void applyControlOutput(const upperlimb_robot::ControlOutputCache &output)
  {
    applyPositionOutput(output);
    applyTorqueOutput(output);
  }

  // ===================== 单轴切到位置模式 =====================
  //
  // 作用：
  // 1. 先停掉当前规划运动
  // 2. 清零 PT 命令
  // 3. 切到 EtherCAT 位置模式
  // 4. 再同步当前位置，避免跳变
  //
  bool ensureAxisInPositionMode(std::size_t i)
  {
    if (i >= upperlimb_robot::AXIS_NUM)
    {
      return false;
    }

    if (!isControlledAxisIndex(i))
    {
      return false;
    }

    const int axis = axis_ids_[i];

    const short rtn_stop =
        GTN_Stop(core_id_, static_cast<long>(1L << (axis - 1)), 0);
    if (rtn_stop != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "切回位置模式前停止轴%d失败，错误码=%d", axis, rtn_stop);
      return false;
    }

    const short rtn_zero = GTN_SetEcatAxisPT(core_id_, axis, 0);
    if (rtn_zero != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "切回位置模式前清零 PT 失败，轴%d，错误码=%d", axis, rtn_zero);
      return false;
    }

    const short rtn_mode = GTN_SetEcatAxisMode(core_id_, axis, 8);
    if (rtn_mode != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "GTN_SetEcatAxisMode 设置位置模式失败，轴%d，错误码=%d",
          axis, rtn_mode);
      return false;
    }

    unsigned short actual_mode = static_cast<unsigned short>(-1);
    short rtn_get_mode = 0;
    bool mode_ok = false;

    // EtherCAT 轴模式切换不是严格同步完成的。
    // SetEcatAxisMode 返回成功后，立即 GetEcatAxisMode 可能仍读到旧模式。
    // 因此这里短暂轮询，避免把正常的切换延迟误判为失败。
    for (int retry = 0; retry < 8; ++retry)
    {
      rtn_get_mode = GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0 && actual_mode == 8)
      {
        mode_ok = true;
        break;
      }

      std::this_thread::sleep_for(5ms);
    }

    if (!mode_ok)
    {
      if (rtn_get_mode != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "读取轴%d当前模式失败，错误码=%d", axis, rtn_get_mode);
      }
      else
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "轴%d 期望切到位置模式，但当前模式=%d", axis, actual_mode);
      }
      return false;
    }

    int32_t enc_pos = 0;
    const short rtn_get_enc = GTN_GetEcatEncPos(core_id_, axis, &enc_pos);
    if (rtn_get_enc != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "读取轴%d编码器位置失败，错误码=%d", axis, rtn_get_enc);
      return false;
    }

    const short rtn_set_prf = GTN_SetPrfPos(core_id_, axis, enc_pos);
    if (rtn_set_prf != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "同步轴%d规划位置失败，错误码=%d", axis, rtn_set_prf);
      return false;
    }

    const short rtn_set_enc = GTN_SetEncPos(core_id_, axis, enc_pos);
    if (rtn_set_enc != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "同步轴%d编码器位置失败，错误码=%d", axis, rtn_set_enc);
      return false;
    }

    // ===================== 新增：同步 axis / profile / encoder =====================
    const short rtn_sync =
        GTN_SynchAxisPos(core_id_, static_cast<long>(1L << (axis - 1)));
    if (rtn_sync != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "同步轴%d axis/profile/encoder 失败，错误码=%d", axis, rtn_sync);
      return false;
    }

    axis_in_torque_mode_[i] = false;
    last_target_torque_[i] = 0.0;
    command_sent_[i] = false;
    position_profile_configured_[i] = false;
    return true;
  }

  // ===================== 单轴切到扭矩模式 =====================
  bool ensureAxisInTorqueMode(std::size_t i)
  {
    if (i >= upperlimb_robot::AXIS_NUM)
    {
      return false;
    }

    if (!isControlledAxisIndex(i))
    {
      return false;
    }

    const int axis = axis_ids_[i];

    const short rtn_stop =
        GTN_Stop(core_id_, static_cast<long>(1L << (axis - 1)), 0);
    if (rtn_stop != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "切到扭矩模式前停止轴%d失败，错误码=%d", axis, rtn_stop);
      return false;
    }

    const short rtn_mode = GTN_SetEcatAxisMode(core_id_, axis, 10);
    if (rtn_mode != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "GTN_SetEcatAxisMode 设置扭矩模式失败，轴%d，错误码=%d",
          axis, rtn_mode);
      return false;
    }

    unsigned short actual_mode = static_cast<unsigned short>(-1);
    short rtn_get_mode = 0;
    bool mode_ok = false;

    // EtherCAT 轴模式切换有生效延迟。
    // 日志中出现“先读到 8，随后恢复时又读到 10”，说明不能只读一次就判失败。
    for (int retry = 0; retry < 8; ++retry)
    {
      rtn_get_mode = GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0 && actual_mode == 10)
      {
        mode_ok = true;
        break;
      }

      std::this_thread::sleep_for(5ms);
    }

    if (!mode_ok)
    {
      if (rtn_get_mode != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "读取轴%d当前模式失败，错误码=%d", axis, rtn_get_mode);
      }
      else
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "轴%d 期望切到扭矩模式，但当前模式=%d", axis, actual_mode);
      }
      return false;
    }

    axis_in_torque_mode_[i] = true;
    command_sent_[i] = false;
    position_profile_configured_[i] = false;
    return true;
  }

  // ===================== 清除全部位置命令缓存 =====================
  //
  // 作用：
  // 1. 强制下一轮位置目标重新发送
  // 2. 强制下一轮重新配置 Trap 参数
  //
  void invalidateAllPositionCommandCache()
  {
    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      command_sent_[i] = false;
      position_profile_configured_[i] = false;
    }
  }

  // ===================== 停止全部轴当前运动（不下使能） =====================
  //
  // 作用：
  // 退出预设位置模式时，先把残余位置运动停掉，
  // 避免未完成的旧位置命令继续影响下一模式。
  //
  void stopAllAxesMotionOnly()
  {
    long mask = 0;

    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        continue;
      }

      if (!axis_enabled_[i])
      {
        continue;
      }

      const int axis = axis_ids_[i];
      mask |= (1L << (axis - 1));
    }

    if (mask == 0)
    {
      return;
    }

    const short rtn = GTN_Stop(core_id_, mask, 0);
    if (rtn != 0)
    {
      RCLCPP_ERROR_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "GTN_Stop 停止当前运动失败，mask=0x%lx，错误码=%d",
          mask, rtn);
    }
  }

  // ===================== 全部轴恢复到位置模式 =====================
  //
  // 作用：
  // 1. 对当前仍停留在扭矩模式的轴，显式切回位置模式
  // 2. 清除位置命令缓存与 Trap 配置缓存
  // 3. 保证下一次位置模式下发时，目标和参数一定重新发送
  //
  void restoreAllAxesToPositionMode()
  {
    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        axis_in_torque_mode_[i] = false;
        command_sent_[i] = false;
        position_profile_configured_[i] = false;
        continue;
      }

      const int axis = axis_ids_[i];

      unsigned short actual_mode = -1;
      const short rtn_get_mode = GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0)
      {
        axis_in_torque_mode_[i] = (actual_mode == 10);
      }

      const bool need_force_restore = (i == 17 || i == 18 || i == 19);

      if (!axis_in_torque_mode_[i] && !need_force_restore)
      {
        continue;
      }

      (void)ensureAxisInPositionMode(i);
    }

    invalidateAllPositionCommandCache();
  }

  // ===================== 执行位置输出 =====================
  //
  // 设计要点：
  // 1. 不再在每次位置变化时都重复调用 GTN_PrfTrap / GTN_SetTrapPrm / GTN_SetVel
  // 2. 只有在“第一次启用该轴位置控制”或“轨迹参数变化”时，才重新配置 Trap
  // 3. 位置模式第一次接管该轴时，无论该轴此前是否在扭矩模式，
  //    都重新同步当前编码器位置 -> 规划位置，避免规划起点陈旧
  //
  void applyPositionOutput(const upperlimb_robot::ControlOutputCache &output)
  {
    long update_mask = 0;
    const bool dual_arm_torque_mode = isDualArmTorqueMode(applied_mode_);

    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        command_sent_[i] = false;
        position_profile_configured_[i] = false;
        last_target_torque_[i] = 0.0;
        continue;
      }

      // 纯双臂扭矩模式下，算法层只输出14个主动轴扭矩。
      // 末端 fixed 轴 8~10 / 18~20 不在控制循环内做位置保持、模式读取或 PT 清理，
      // 避免继续触发 SetPos / SetTrapPrm / SetVel / SyncAxisPos 类错误。
      if (dual_arm_torque_mode && output.use_torque[i])
      {
        command_sent_[i] = false;
        position_profile_configured_[i] = false;
        continue;
      }

      if (dual_arm_torque_mode && !output.use_position[i])
      {
        command_sent_[i] = false;
        position_profile_configured_[i] = false;
        continue;
      }

      const int axis = axis_ids_[i];

      unsigned short actual_mode = static_cast<unsigned short>(-1);
      const short rtn_get_mode = GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0)
      {
        axis_in_torque_mode_[i] = (actual_mode == 10);
      }

      if (output.use_torque[i])
      {
        command_sent_[i] = false;
        position_profile_configured_[i] = false;
        continue;
      }

      if (!output.use_position[i])
      {
        command_sent_[i] = false;
        position_profile_configured_[i] = false;

        if (axis_in_torque_mode_[i])
        {
          (void)ensureAxisInPositionMode(i);
        }
        continue;
      }

      if (axis_in_torque_mode_[i])
      {
        if (!ensureAxisInPositionMode(i))
        {
          continue;
        }
      }

      const double target_deg = output.target_position[i];
      const double target_pulse =
          upperlimb_robot::jointDegToPulse(axis, target_deg);

      const double vel_deg = output.target_velocity[i];
      const double acc_deg = output.target_acc[i];
      const double dec_deg = output.target_dec[i];
      const short smooth_time = output.target_smooth_time[i];

      bool need_reconfigure_profile = false;

      if (!position_profile_configured_[i])
      {
        need_reconfigure_profile = true;
      }
      else
      {
        if (std::abs(vel_deg - last_profile_velocity_[i]) > 1e-6 ||
            std::abs(acc_deg - last_profile_acc_[i]) > 1e-6 ||
            std::abs(dec_deg - last_profile_dec_[i]) > 1e-6 ||
            smooth_time != last_profile_smooth_time_[i])
        {
          need_reconfigure_profile = true;
        }
      }

      if (need_reconfigure_profile)
      {
        int32_t enc_pos = 0;
        short rtn = GTN_GetEcatEncPos(core_id_, axis, &enc_pos);
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "读取轴%d编码器位置失败，错误码=%d", axis, rtn);
          continue;
        }

        rtn = GTN_SetPrfPos(core_id_, axis, enc_pos);
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "同步轴%d规划位置失败，错误码=%d", axis, rtn);
          continue;
        }

        rtn = GTN_SetEncPos(core_id_, axis, enc_pos);
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "同步轴%d编码器位置失败，错误码=%d", axis, rtn);
          continue;
        }

        // ===================== 新增：同步 axis / profile / encoder =====================
        rtn = GTN_SynchAxisPos(core_id_, static_cast<long>(1L << (axis - 1)));
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "同步轴%d axis/profile/encoder 失败，错误码=%d", axis, rtn);
          continue;
        }

        rtn = GTN_PrfTrap(core_id_, axis);
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "GTN_PrfTrap 轴%d失败，错误码=%d", axis, rtn);
          continue;
        }

        TTrapPrm trap{};
        trap.acc =
            upperlimb_robot::jointAccelDegPerSec2ToPulsePerMs2(axis, acc_deg);
        trap.dec =
            upperlimb_robot::jointAccelDegPerSec2ToPulsePerMs2(axis, dec_deg);
        trap.smoothTime = smooth_time;
        trap.velStart = 0;

        rtn = GTN_SetTrapPrm(core_id_, axis, &trap);
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "GTN_SetTrapPrm 轴%d失败，错误码=%d", axis, rtn);
          continue;
        }

        rtn = GTN_SetVel(
            core_id_,
            axis,
            upperlimb_robot::jointSpeedDegPerSecToPulsePerMs(axis, vel_deg));
        if (rtn != 0)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "GTN_SetVel 轴%d失败，错误码=%d", axis, rtn);
          continue;
        }

        position_profile_configured_[i] = true;
        last_profile_velocity_[i] = vel_deg;
        last_profile_acc_[i] = acc_deg;
        last_profile_dec_[i] = dec_deg;
        last_profile_smooth_time_[i] = smooth_time;
      }

      if (command_sent_[i] &&
          std::abs(target_deg - last_target_position_[i]) < position_epsilon_)
      {
        continue;
      }

      const short rtn_set_pos =
          GTN_SetPos(core_id_, axis, static_cast<int32_t>(target_pulse));
      if (rtn_set_pos != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "GTN_SetPos 轴%d失败，错误码=%d", axis, rtn_set_pos);
        continue;
      }

      update_mask |= (1L << (axis - 1));
      last_target_position_[i] = target_deg;
      command_sent_[i] = true;
    }

    if (update_mask != 0)
    {
      const short rtn = GTN_Update(core_id_, update_mask);
      if (rtn != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "GTN_Update 失败，mask=0x%lx，错误码=%d",
            update_mask, rtn);
      }
    }
  }

  // ===================== 执行扭矩输出 =====================
  //
  // 1. use_torque == true 时，确保切到扭矩模式
  // 2. use_torque == false 时，如果该轴还停留在扭矩模式，则清零并切回位置模式
  //
  void applyTorqueOutput(const upperlimb_robot::ControlOutputCache &output)
  {
    const bool dual_arm_torque_mode = isDualArmTorqueMode(applied_mode_);

    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        axis_in_torque_mode_[i] = false;
        last_target_torque_[i] = 0.0;
        continue;
      }

      // 纯双臂扭矩模式下，非14个主动扭矩轴完全跳过。
      if (dual_arm_torque_mode && !output.use_torque[i])
      {
        last_target_torque_[i] = 0.0;
        continue;
      }

      const int axis = axis_ids_[i];

      unsigned short actual_mode = static_cast<unsigned short>(-1);
      const short rtn_get_mode =
          GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0)
      {
        axis_in_torque_mode_[i] = (actual_mode == 10);
      }

      // 当前轴不再请求扭矩控制时，先清零PT，再恢复位置模式。
      if (!output.use_torque[i])
      {
        if (axis_in_torque_mode_[i])
        {
          const short rtn_zero = GTN_SetEcatAxisPT(core_id_, axis, 0);
          if (rtn_zero != 0)
          {
            RCLCPP_ERROR_THROTTLE(
                this->get_logger(), *this->get_clock(), 2000,
                "GTN_SetEcatAxisPT 清零失败，轴%d，错误码=%d", axis, rtn_zero);
          }

          if (!dual_arm_torque_mode)
          {
            (void)ensureAxisInPositionMode(i);
          }
        }

        last_target_torque_[i] = 0.0;
        continue;
      }

      const double test_raw = upperlimb_robot::torqueNmToRaw(axis, 1.0);
      if (test_raw == 0.0)
      {
        RCLCPP_WARN_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "轴%d 当前没有有效扭矩标定系数，跳过扭矩输出", axis);
        continue;
      }

      const double target_torque_nm = output.target_torque[i];
      if (!std::isfinite(target_torque_nm))
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "轴%d 目标扭矩为NaN或Inf，本轮不发送", axis);
        continue;
      }

      // 先确保轴已经处于扭矩模式，再判断是否需要重复发送。
      // 这样第一帧即使目标扭矩与缓存值相同，也不会漏掉模式切换。
      bool switched_to_torque_mode = false;

      if (!axis_in_torque_mode_[i])
      {
        if (dual_arm_torque_mode)
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "双臂扭矩模式下轴%d 未处于扭矩模式，本轮跳过 PT；不在控制循环内反复切模式",
              axis);
          continue;
        }

        if (!ensureAxisInTorqueMode(i))
        {
          RCLCPP_ERROR_THROTTLE(
              this->get_logger(), *this->get_clock(), 2000,
              "轴%d 切入扭矩模式失败，本轮不发送PT", axis);
          continue;
        }

        switched_to_torque_mode = true;
      }

      if (!switched_to_torque_mode &&
          std::abs(target_torque_nm - last_target_torque_[i]) < torque_epsilon_)
      {
        continue;
      }

      const double torque_raw_double =
          upperlimb_robot::torqueNmToRaw(axis, target_torque_nm);

      if (!std::isfinite(torque_raw_double))
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "轴%d 扭矩单位换算结果非法，本轮不发送", axis);
        continue;
      }

      const short torque_raw =
          static_cast<short>(std::lround(torque_raw_double));

      const short rtn_pt = GTN_SetEcatAxisPT(core_id_, axis, torque_raw);
      if (rtn_pt != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "GTN_SetEcatAxisPT 发送扭矩失败，轴%d，目标扭矩=%.4f Nm，raw=%d，错误码=%d",
            axis, target_torque_nm, torque_raw, rtn_pt);
        continue;
      }

      last_target_torque_[i] = target_torque_nm;
    }
  }

  // ===================== 清零全部扭矩命令 =====================
  void clearAllTorqueCommands()
  {
    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        axis_in_torque_mode_[i] = false;
        last_target_torque_[i] = 0.0;
        continue;
      }

      const int axis = axis_ids_[i];

      unsigned short actual_mode = -1;
      const short rtn_get_mode = GTN_GetEcatAxisMode(core_id_, axis, &actual_mode);
      if (rtn_get_mode == 0)
      {
        axis_in_torque_mode_[i] = (actual_mode == 10);
      }

      if (!axis_in_torque_mode_[i])
      {
        continue;
      }
      const short rtn = GTN_SetEcatAxisPT(core_id_, axis, 0);
      if (rtn != 0)
      {
        RCLCPP_ERROR_THROTTLE(
            this->get_logger(), *this->get_clock(), 2000,
            "清零扭矩命令失败，轴%d，错误码=%d", axis, rtn);
      }

      last_target_torque_[i] = 0.0;
    }
  }

  // ===================== 停止全部轴 =====================
  bool stopAllAxesRaw()
  {
    if (!controller_opened_)
    {
      return true;
    }

    bool all_ok = true;
    int failed_axes = 0;

    for (std::size_t i = 0; i < upperlimb_robot::AXIS_NUM; ++i)
    {
      if (!isControlledAxisIndex(i))
      {
        continue;
      }

      const int axis = axis_ids_[i];

      if (!axis_enabled_[i])
      {
        continue;
      }

      short rtn_stop =
          GTN_Stop(core_id_, static_cast<long>(1L << (axis - 1)), 0);
      if (rtn_stop != 0)
      {
        fprintf(stderr, "停止轴%d失败，错误码=%d\n", axis, rtn_stop);
        fflush(stderr);
        all_ok = false;
        failed_axes++;
      }

      short rtn_off = GTN_AxisOff(core_id_, axis);
      if (rtn_off != 0)
      {
        fprintf(stderr, "关闭轴%d使能失败，错误码=%d\n", axis, rtn_off);
        fflush(stderr);
        all_ok = false;
        failed_axes++;
      }
      else
      {
        axis_enabled_[i] = false;
      }
    }

    if (!all_ok)
    {
      fprintf(stderr, "共有 %d 个轴关闭过程出现错误。\n", failed_axes);
      fflush(stderr);
    }

    return all_ok;
  }

  // ===================== JointState 转换 =====================
  //
  // URDF 定义：
  // joint1  ~ joint10  -> 左臂
  // joint11 ~ joint20  -> 右臂
  //
  // 控制层内部状态：
  // state[10~19] -> 左臂
  // state[0~9]   -> 右臂
  //
  sensor_msgs::msg::JointState convertToJointStateMsg(
      const upperlimb_robot::MotorStateCache &state)
  {
    sensor_msgs::msg::JointState msg;
    msg.header.stamp = this->now();

    msg.name = {
        "joint1", "joint2", "joint3", "joint4", "joint5",
        "joint6", "joint7", "joint8", "joint9", "joint10",
        "joint11", "joint12", "joint13", "joint14", "joint15",
        "joint16", "joint17", "joint18", "joint19", "joint20"};

    msg.position.resize(20);
    msg.velocity.resize(20);
    msg.effort.resize(20);

    constexpr double deg_to_rad = M_PI / 180.0;

    for (std::size_t src = 10, dst = 0; src < 20; ++src, ++dst)
    {
      msg.position[dst] = state.position[src] * deg_to_rad;
      msg.velocity[dst] = state.velocity[src] * deg_to_rad;
      msg.effort[dst] = state.torque[src];
    }

    for (std::size_t src = 0, dst = 10; src < 10; ++src, ++dst)
    {
      msg.position[dst] = state.position[src] * deg_to_rad;
      msg.velocity[dst] = state.velocity[src] * deg_to_rad;
      msg.effort[dst] = state.torque[src];
    }

    return msg;
  }

private:
  rclcpp::Subscription<upperlimb_robot::msg::ControlCommand>::SharedPtr control_command_sub_;
  rclcpp::Publisher<upperlimb_robot::msg::SystemState>::SharedPtr system_pub_;
  rclcpp::Publisher<upperlimb_robot::msg::RobotState>::SharedPtr robot_state_pub_;
  rclcpp::Publisher<upperlimb_robot::msg::SsvepResult>::SharedPtr ssvep_result_pub_;
  rclcpp::Publisher<upperlimb_robot::msg::SsvepActionStatus>::SharedPtr ssvep_status_pub_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;
  rclcpp::TimerBase::SharedPtr state_timer_;
  rclcpp::TimerBase::SharedPtr ssvep_status_timer_;

  bool joint_init_ = false;
  bool controller_init_ = false;
  bool system_ready_ = false;

  bool controller_opened_ = false;
  bool ecat_started_ = false;
  bool shutdown_done_ = false;
  bool hardware_enabled_ = true;
  std::string serial_device_;

  std::atomic<bool> running_{false};
  std::atomic<bool> state_ready_{false};

  std::thread state_read_thread_;
  std::thread control_thread_;
  std::thread serial_thread_;

  std::chrono::steady_clock::time_point last_control_time_{};
  bool last_control_time_valid_ = false;
  bool ssvep_fault_safe_done_ = false;

  std::atomic<int> current_mode_{upperlimb_robot::MODE_IDLE};
  int applied_mode_{upperlimb_robot::MODE_IDLE};

  bool mode_enter_failed_ = false;
  int mode_enter_fallback_mode_ = upperlimb_robot::MODE_IDLE;

  std::atomic<int> state_hz_{50};
  std::atomic<int> control_hz_{50};
  std::atomic<int> pending_ssvep_target_{-1};
  std::atomic<bool> ssvep_debug_requested_{true};
  std::atomic<bool> ssvep_reconfigure_requested_{false};
  std::atomic<bool> emergency_stop_requested_{false};
  std::atomic<bool> serial_connected_{false};

  int status_read_divider_ = 20;
  int status_read_divider_count_ = 0;

  std::mutex state_mutex_;
  upperlimb_robot::MotorStateCache latest_motor_state_;

  std::mutex sensor_mutex_;
  upperlimb_robot::SensorStateCache latest_sensor_state_;

  mutable std::mutex ssvep_mutex_;
  upperlimb_robot::SsvepControl ssvep_control_;
  upperlimb_robot::MotorStateCache ssvep_simulated_state_;
  int simulation_publish_count_ = 0;

  // GTN/EtherCAT 底层库互斥锁：状态采集线程和控制线程必须串行访问控制卡库。
  std::mutex gtn_mutex_;

  int publish_divider_ = 10;
  int publish_divider_count_ = 0;

  int core_id_ = 1;

  std::array<int, upperlimb_robot::AXIS_NUM> axis_ids_ = {
      1, 2, 3, 4, 5,
      6, 7, 8, 9, 10,
      11, 12, 13, 14, 15,
      16, 17, 18, 19, 20};

  std::array<int32_t, upperlimb_robot::AXIS_NUM> enc_pos_{};
  std::array<bool, upperlimb_robot::AXIS_NUM> axis_enabled_{};

  // ===================== 位置命令缓存 =====================
  //
  // last_target_position_ :
  // 记录上一次发送的位置目标（单位 deg）
  //
  // command_sent_ :
  // 标记该轴是否已经发送过位置命令
  //
  std::array<double, upperlimb_robot::AXIS_NUM> last_target_position_{};
  std::array<bool, upperlimb_robot::AXIS_NUM> command_sent_{};

  // ===================== 扭矩模式状态缓存 =====================
  //
  // axis_in_torque_mode_ :
  // 标记该轴当前是否处于扭矩模式
  //
  // last_target_torque_ :
  // 记录上一次发送的扭矩目标（单位 Nm）
  //
  std::array<bool, upperlimb_robot::AXIS_NUM> axis_in_torque_mode_{};
  std::array<double, upperlimb_robot::AXIS_NUM> last_target_torque_{};

  // ===================== 位置规划参数缓存 =====================
  //
  // 作用：
  // 1. 避免在连续轨迹模式下，每个周期都重复配置 Trap 参数
  // 2. 只有在速度/加速度/减速度/平滑时间变化时，才重新配置
  //
  std::array<bool, upperlimb_robot::AXIS_NUM> position_profile_configured_{};
  std::array<double, upperlimb_robot::AXIS_NUM> last_profile_velocity_{};
  std::array<double, upperlimb_robot::AXIS_NUM> last_profile_acc_{};
  std::array<double, upperlimb_robot::AXIS_NUM> last_profile_dec_{};
  std::array<short, upperlimb_robot::AXIS_NUM> last_profile_smooth_time_{};

  double position_epsilon_ = 0.05;
  double torque_epsilon_ = 0.01;
};

static std::shared_ptr<RobotControlNode> g_node = nullptr;

void signal_handler(int signum)
{
  fprintf(stderr, "\n收到退出信号(%d)，开始安全关闭...\n", signum);
  fflush(stderr);

  if (g_node)
  {
    g_node->shutdownHardware();
  }

  rclcpp::shutdown();
}

int main(int argc, char const *argv[])
{
  rclcpp::init(argc, argv);

  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  g_node = std::make_shared<RobotControlNode>();

  rclcpp::spin(g_node);

  if (g_node)
  {
    g_node->shutdownHardware();
    g_node.reset();
  }

  return 0;
}
