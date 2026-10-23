#include "upperlimb_robot/control_algorithms.hpp"

#include <cstdlib>
#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <algorithm>
#include <array>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include <ament_index_cpp/get_package_share_directory.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>

#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/rnea.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <pinocchio/algorithm/jacobian.hpp>
#include <pinocchio/spatial/force.hpp>

namespace upperlimb_robot
{

  // ===================== 全局统一重力补偿参数 =====================
  //
  // 所有保留的零力控制模式共用这两套参数，以后只需在这里调节一次。
  //
  // 左臂顺序：joint1~joint7
  const GravityCompensationParameters LEFT_ARM_GRAVITY_COMPENSATION{
      {1.25, 1.05, 1.00, 1.00, 1.00, 1.00, 1.00},
      {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}};

  // 右臂顺序：joint11~joint17
  const GravityCompensationParameters RIGHT_ARM_GRAVITY_COMPENSATION{
      {1.25, 1.05, 1.00, 1.00, 1.00, 1.00, 1.00},
      {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00}};

  // ===================== 全局统一关节摩擦补偿参数 =====================
  //
  // 所有扭矩模式共用这两套参数。
  // coulomb_nm 初始为 0，待逐关节实机标定后再增加。
  // viscous_nm_per_rad_s 初始沿用原双臂零力模式中的 +0.4*dq 助力效果。
  // velocity_smooth_rad_s 用于避免速度在零附近换向时库仑项跳变。
  //
  // 左臂顺序：joint1~joint7
  const FrictionCompensationParameters LEFT_ARM_FRICTION_COMPENSATION{
      {0.20, 0.20, 0.15, 0.15, 0.10, 0.10, 0.08},
      {0.40, 0.40, 0.40, 0.40, 0.40, 0.40, 0.40},
      {0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03}};

  // 右臂顺序：joint11~joint17
  //
  // coulomb_nm 使用较小的初始值补偿低速库仑摩擦。
  // 这些值只作为保守起点，后续应根据实机逐关节标定继续微调。
  //
  // viscous_nm_per_rad_s 仍保留原来的 +0.4*dq 运动助力；
  // velocity_smooth_rad_s 缩小到 0.03 rad/s，使低速区更快建立摩擦补偿，
  // 同时仍通过 tanh 保持过零连续，避免直接 sign() 带来的跳变。
  const FrictionCompensationParameters RIGHT_ARM_FRICTION_COMPENSATION{
      {0.20, 0.20, 0.15, 0.15, 0.10, 0.10, 0.08},
      {0.40, 0.40, 0.40, 0.40, 0.40, 0.40, 0.40},
      {0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03}};

  namespace
  {

    // ===================== 编码器参数 =====================
    //
    // 每度对应的脉冲数，单位：pulse/deg
    //
    // 不同轴使用的编码器分辨率不同，所以这里准备了 3 套常量。
    // 后面在 joint_map 里按轴选择对应的 per_angle。
    //
    constexpr double PerAngle00 = 524288.0 / 360.0;
    constexpr double PerAngle01 = 262144.0 / 360.0;
    constexpr double PerAngle02 = 2048.0 / 360.0;

    // ===================== 零位偏置 =====================
    //
    // zero_offset 的单位是 deg。
    // 这些值用于“电机编码器零位”和“关节物理零位”之间的对应换算。
    //
    // 左臂零位偏置角，单位：deg
    //
    constexpr double SZO10 = 249.46;
    constexpr double SZO20 = 12172.4808;
    constexpr double SZO30 = -12.1935;
    constexpr double SZO40 = 0;
    constexpr double SZO50 = 23313.27;
    constexpr double SZO60 = -728.71;
    constexpr double SZO70 = -119.21;
    constexpr double SZO80 = -23.2018;
    constexpr double SZO90 = -23.2018;
    constexpr double SZO100 = -833.12;

    // 右臂零位偏置角，单位：deg
    constexpr double SZRO10 = -1168.8423;
    constexpr double SZRO20 = -100.2187;
    constexpr double SZRO30 = 1009.6985;
    constexpr double SZRO40 = -157.2542;
    constexpr double SZRO50 = 76.6393;
    constexpr double SZRO60 = 1231.8668;
    constexpr double SZRO70 = 6597.68;
    constexpr double SZRO80 = -447.8906;
    constexpr double SZRO90 = 0.0;
    constexpr double SZRO100 = -1200.0;

    // ===================== 单轴参数表 =====================
    //
    // 这里定义每个物理轴（axis=1~20）的换算参数。
    //
    // 字段说明：
    // per_angle    : 每度对应多少脉冲，单位 pulse/deg
    // zero_offset  : 零位偏置，单位 deg
    // ratio        : 电机角 / 关节角 的减速比
    // torque_scale : 扭矩换算比例，单位 Nm/raw
    //
    // 注意：
    // 1. 这里的 axis 是“物理轴号 1~20”
    // 2. 不是控制层数组索引 0~19
    //
    struct JointParam
    {
      double per_angle;    // pulse / deg
      double zero_offset;  // deg
      double ratio;        // 电机角 / 关节角
      double torque_scale; // Nm / raw
    };

    constexpr JointParam joint_map[21] = {
        {},

        // ===================== 右臂 1~10 =====================
        //
        // 物理轴号 1~10 对应右臂
        //
        {PerAngle01, SZRO10, 121.0, 61.0 / 1000.0},
        {PerAngle00, SZRO20, 121.0, 61.0 / 1000.0},
        {PerAngle01, SZRO30, 121.0, 43.68 / 1000.0},
        {PerAngle01, SZRO40, 101.0, 49.0 / 1000.0},
        {PerAngle01, SZRO50, 121.0, 43.68 / 1000.0},
        {PerAngle00, SZRO60, 101.0, 36.4 / 1000.0},
        {PerAngle01, SZRO70, 100.0, 18.0 / 1000.0},
        {PerAngle02, SZRO80, 2048.0, 0.0},
        {PerAngle01, SZRO90, 100.0, 3.9 / 1000.0},
        {PerAngle00, SZRO100, 100.0, 3.9 / 1000.0},

        // ===================== 左臂 11~20 =====================
        //
        // 物理轴号 11~20 对应左臂
        //
        {PerAngle00, SZO10, 121.0, 61.0 / 1000.0},
        {PerAngle01, SZO20, 121.0, 61.0 / 1000.0},
        {PerAngle01, SZO30, 121.0, 43.68 / 1000.0},
        {PerAngle01, SZO40, 101.0, 49.0 / 1000.0},
        {PerAngle01, SZO50, 121.0, 43.68 / 1000.0},
        {PerAngle00, SZO60, 101.0, 36.4 / 1000.0},
        {PerAngle01, SZO70, 100.0, 18.0 / 1000.0},
        {PerAngle02, SZO80, 2048.0, 0.0},
        {PerAngle01, SZO90, 100.0, 3.9 / 1000.0},
        {PerAngle01, SZO100, 100.0, 3.9 / 1000.0},
    };

    // ===================== 判断是否为左臂物理轴 =====================
    //
    // 输入：
    // axis -> 真实物理轴号 1~20
    //
    // 返回：
    // true  -> 左臂物理轴 11~20
    // false -> 非左臂物理轴
    //
    inline bool isLeftAxis(int axis)
    {
      return axis >= 11 && axis <= 20;
    }

    // ===================== 获取单轴参数 =====================
    //
    // 输入：
    // axis -> 真实物理轴号 1~20
    //
    // 返回：
    // 对应轴的参数指针；非法轴号返回 nullptr
    //
    inline const JointParam *getJointParam(int axis)
    {
      if (axis < 1 || axis > 20)
      {
        return nullptr;
      }
      return &joint_map[axis];
    }

    // ===================== 幅值换算辅助函数 =====================
    //
    // 这两个函数只取“速度/加速度的大小”，不保留正负方向。
    // 主要用于预设位姿模式下配置 Trap 参数。
    //
    // 说明：
    // Trap 运动参数中的 vel / acc / dec 一般只需要幅值，
    // 方向由“当前位置 -> 目标位置”的相对关系自动决定。
    //

    // pulse/ms -> deg/s（只保留幅值）
    inline double pulsePerMsToJointSpeedDegPerSecMagnitude(int axis, double pulse_per_ms)
    {
      const auto *p = getJointParam(axis);
      if (p == nullptr)
      {
        return 0.0;
      }

      return std::abs(pulse_per_ms) / (p->per_angle * p->ratio) * 1000.0;
    }

    // pulse/ms^2 -> deg/s^2（只保留幅值）
    inline double pulsePerMs2ToJointAccelDegPerSec2Magnitude(int axis, double pulse_per_ms2)
    {
      const auto *p = getJointParam(axis);
      if (p == nullptr)
      {
        return 0.0;
      }

      return std::abs(pulse_per_ms2) / (p->per_angle * p->ratio) * 1000000.0;
    }

    // 单臂独立 URDF 中，7 个主动关节的 v 索引固定为 0~6。
    constexpr std::array<int, 7> SINGLE_ARM_V_IDS = {0, 1, 2, 3, 4, 5, 6};

    // 对 Pinocchio 原始重力向量进行逐关节比例和偏置修正。
    // gravity 中未属于当前机械臂的其他关节保持不变。
    inline void applyArmGravityCompensation(
        Eigen::VectorXd &gravity,
        const std::array<int, 7> &v_ids,
        const GravityCompensationParameters &parameters)
    {
      for (std::size_t i = 0; i < 7; ++i)
      {
        const int v_id = v_ids[i];
        if (v_id < 0 || v_id >= gravity.size())
        {
          continue;
        }

        gravity(v_id) =
            parameters.gain[i] * gravity(v_id) +
            parameters.bias_nm[i];
      }
    }

    // 计算单个关节的摩擦补偿力矩。
    // 返回值使用 Pinocchio 模型关节方向，且与 joint_velocity_rad_s 同方向。
    inline double calculateJointFrictionCompensation(
        double joint_velocity_rad_s,
        std::size_t joint_index,
        const FrictionCompensationParameters &parameters)
    {
      if (joint_index >= 7 || !std::isfinite(joint_velocity_rad_s))
      {
        return 0.0;
      }

      const double coulomb = parameters.coulomb_nm[joint_index];
      const double viscous = parameters.viscous_nm_per_rad_s[joint_index];
      const double smooth = parameters.velocity_smooth_rad_s[joint_index];

      if (!std::isfinite(coulomb) ||
          !std::isfinite(viscous) ||
          !std::isfinite(smooth) ||
          smooth <= 0.0)
      {
        return 0.0;
      }

      const double tau_coulomb =
          coulomb * std::tanh(joint_velocity_rad_s / smooth);

      const double tau_viscous =
          viscous * joint_velocity_rad_s;

      return tau_coulomb + tau_viscous;
    }

    // 将当前机械臂的逐关节摩擦补偿叠加到已有模型补偿力矩中。
    // torque 可以是已完成重力修正的向量，也可以是单独创建的补偿向量。
    inline void addArmFrictionCompensation(
        Eigen::VectorXd &torque,
        const Eigen::VectorXd &velocity,
        const std::array<int, 7> &v_ids,
        const FrictionCompensationParameters &parameters)
    {
      for (std::size_t i = 0; i < 7; ++i)
      {
        const int v_id = v_ids[i];

        if (v_id < 0 ||
            v_id >= torque.size() ||
            v_id >= velocity.size())
        {
          continue;
        }

        torque(v_id) +=
            calculateJointFrictionCompensation(
                velocity(v_id), i, parameters);
      }
    }

  } // namespace

  SsvepFrameResult parseSsvepProtocolFrame(
      const std::string &raw,
      std::int64_t &last_sequence)
  {
    SsvepFrameResult result;
    std::vector<std::string> fields;
    std::stringstream stream(raw);
    std::string field;
    while (std::getline(stream, field, ','))
    {
      fields.push_back(field);
    }

    if (fields.size() != 5 || fields[0] != "RESULT")
    {
      result.detail = "字段数或消息头错误";
      return result;
    }

    const auto only_digits = [](const std::string &value)
    {
      return !value.empty() && std::all_of(
          value.begin(), value.end(),
          [](unsigned char c) { return c >= '0' && c <= '9'; });
    };
    const auto has_whitespace = [](const std::string &value)
    {
      return std::any_of(
          value.begin(), value.end(),
          [](unsigned char c) { return std::isspace(c) != 0; });
    };

    try
    {
      if (!only_digits(fields[1]) || !only_digits(fields[3]) ||
          has_whitespace(fields[4]))
      {
        throw std::invalid_argument("strict_ascii");
      }

      std::size_t used = 0;
      result.sequence = std::stoull(fields[1], &used);
      if (used != fields[1].size() ||
          result.sequence > static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()) ||
          (fields[2] != "EEG" && fields[2] != "TEST"))
      {
        throw std::invalid_argument("header");
      }

      const int target = std::stoi(fields[3], &used);
      if (used != fields[3].size() || target < 0 || target > 4)
      {
        throw std::invalid_argument("target");
      }

      result.frequency_hz = std::stod(fields[4], &used);
      if (used != fields[4].size() || !std::isfinite(result.frequency_hz) ||
          result.frequency_hz < 0.0 || result.frequency_hz > 200.0)
      {
        throw std::invalid_argument("frequency");
      }

      result.source = fields[2];
      result.target = static_cast<std::uint8_t>(target);
      if (last_sequence >= 0 &&
          result.sequence == static_cast<std::uint64_t>(last_sequence))
      {
        result.status = 2;
        result.detail = "重复序号";
        return result;
      }
      if (last_sequence >= 0 &&
          result.sequence < static_cast<std::uint64_t>(last_sequence))
      {
        result.status = 3;
        result.detail = "旧序号；串口重连前不允许回退";
        return result;
      }

      last_sequence = static_cast<std::int64_t>(result.sequence);
      result.status = 0;
      result.detail = "协议校验通过";
      return result;
    }
    catch (const std::exception &)
    {
      result = SsvepFrameResult{};
      result.detail = "序号、模式、目标或频率不合法";
      return result;
    }
  }

  // ===================== 位置换算 =====================
  //
  // jointDegToPulse / pulseToJointDeg
  //
  // 作用：
  // 在“关节物理角度 deg”和“驱动编码器脉冲 pulse”之间做双向换算。
  //
  // 注意：
  // 1. 输入的 axis 是物理轴号 1~20，不是数组索引 0~19
  // 2. 左右臂方向定义不同，因此公式符号不同
  //

  // 关节角 deg -> 编码器脉冲 pulse
  double jointDegToPulse(int axis, double joint_deg)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    // 左臂方向定义
    if (isLeftAxis(axis))
    {
      return (p->zero_offset + p->ratio * joint_deg) * p->per_angle;
    }

    // 右臂方向定义
    return (p->zero_offset - p->ratio * joint_deg) * p->per_angle;
  }

  // 编码器脉冲 pulse -> 关节角 deg
  double pulseToJointDeg(int axis, double pulse)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    if (isLeftAxis(axis))
    {
      return (pulse / p->per_angle - p->zero_offset) / p->ratio;
    }

    return (p->zero_offset - pulse / p->per_angle) / p->ratio;
  }

  // ===================== 速度换算 =====================
  //
  // jointSpeedDegPerSecToPulsePerMs / pulsePerMsToJointDegPerSec
  //
  // 作用：
  // 在“关节速度 deg/s”和“驱动速度 pulse/ms”之间做双向换算。
  //
  // 注意：
  // 1. 对外统一使用真实物理量 deg/s
  // 2. 底层驱动速度单位是 pulse/ms
  // 3. 左右臂在反馈方向上符号定义不同
  //

  // 关节速度 deg/s -> pulse/ms
  double jointSpeedDegPerSecToPulsePerMs(int axis, double joint_speed_deg_per_sec)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    // 发送给驱动的速度参数通常只需要幅值
    return std::abs(joint_speed_deg_per_sec) * p->per_angle * p->ratio / 1000.0;
  }

  // pulse/ms -> 关节速度 deg/s
  double pulsePerMsToJointDegPerSec(int axis, double pulse_per_ms)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    if (isLeftAxis(axis))
    {
      return (pulse_per_ms / p->per_angle) / p->ratio * 1000.0;
    }

    return -(pulse_per_ms / p->per_angle) / p->ratio * 1000.0;
  }

  // ===================== 加速度换算 =====================
  //
  // jointAccelDegPerSec2ToPulsePerMs2 / pulsePerMs2ToJointDegPerSec2
  //
  // 作用：
  // 在“关节加速度 deg/s^2”和“驱动加速度 pulse/ms^2”之间做双向换算。
  //
  // 注意：
  // 1. 对外统一使用真实物理量 deg/s^2
  // 2. 发送给驱动的 acc/dec 一般只需要幅值
  //

  // 关节加速度 deg/s^2 -> pulse/ms^2
  double jointAccelDegPerSec2ToPulsePerMs2(int axis, double joint_acc_deg_per_sec2)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    return std::abs(joint_acc_deg_per_sec2) * p->per_angle * p->ratio / 1000000.0;
  }

  // pulse/ms^2 -> 关节加速度 deg/s^2
  double pulsePerMs2ToJointDegPerSec2(int axis, double pulse_per_ms2)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    if (isLeftAxis(axis))
    {
      return (pulse_per_ms2 / p->per_angle) / p->ratio * 1000000.0;
    }

    return -(pulse_per_ms2 / p->per_angle) / p->ratio * 1000000.0;
  }

  // ===================== 扭矩换算 =====================
  //
  // torqueRawToNm / torqueNmToRaw
  //
  // 作用：
  // 在“驱动内部扭矩单位 raw”和“物理扭矩单位 Nm”之间做双向换算。
  //
  // 使用约定：
  // 1. 读驱动反馈时：raw -> Nm
  // 2. 算法层 output.target_torque[] 一律使用 Nm
  // 3. 真正下发给驱动前：Nm -> raw
  //
  // 例如：
  // output.target_torque[6] = 2.0;   // 这里的 2.0 是 Nm
  //

  // raw -> Nm
  double torqueRawToNm(int axis, double raw)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr)
    {
      return 0.0;
    }

    return raw * p->torque_scale;
  }

  // Nm -> raw
  double torqueNmToRaw(int axis, double torque_nm)
  {
    const auto *p = getJointParam(axis);
    if (p == nullptr || p->torque_scale == 0.0)
    {
      return 0.0;
    }

    return torque_nm / p->torque_scale;
  }

  // ===================== 空闲模式 =====================
  //
  // 当前实现：
  // 1. 不使用 state
  // 2. 清空 output
  // 3. 标记 output 无效
  //
  // 执行层看到 output.valid == false 后，
  // 会决定本轮不执行控制输出。
  //
  void runIdle(const MotorStateCache &state, ControlOutputCache &output)
  {
    (void)state;
    output = ControlOutputCache{};
    output.valid = false;
  }

  // ===================== 左臂零力模式 =====================
  void runZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output)
  {
    // ===================== 输出初始化 =====================
    //
    // 这里每次进入都先清空 output，
    // 然后只对需要控制的关节写入扭矩输出。
    //
    output = ControlOutputCache{};
    output.valid = false;

    // ===================== 左臂 joint1~joint7 =====================
    //
    // 当前模型设定：
    // 1. URDF 中 joint1~3 已经改成 revolute，joint8~10 保持 fixed
    // 2. Pinocchio 模型现在有 7 个可动关节：joint1~joint7
    // 3. 这里 joint1~7 全部参与零力模式扭矩控制
    //
    // 注意：
    // 下面这 7 个控制层索引，必须与你当前左臂真实映射一致。
    //
    constexpr std::size_t IDX_J1 = 10; // joint1 -> 左臂控制层索引
    constexpr std::size_t IDX_J2 = 11; // joint2 -> 左臂控制层索引
    constexpr std::size_t IDX_J3 = 12; // joint3 -> 左臂控制层索引
    constexpr std::size_t IDX_J4 = 13; // joint4 -> 左臂控制层索引
    constexpr std::size_t IDX_J5 = 14; // joint5 -> 左臂控制层索引
    constexpr std::size_t IDX_J6 = 15; // joint6 -> 左臂控制层索引
    constexpr std::size_t IDX_J7 = 16; // joint7 -> 左臂控制层索引

    // ===================== Pinocchio 懒加载上下文 =====================
    //
    // 不另外写很多函数，直接在本函数里静态初始化。
    // 第一次进入时加载 URDF、查 joint/frame id；
    // 后续周期只做实时计算。
    //
    static bool pin_initialized = false;
    static bool pin_init_failed = false;
    static pinocchio::Model model;
    static std::unique_ptr<pinocchio::Data> data;
    static pinocchio::FrameIndex frame_id_arm = 0;
    static pinocchio::FrameIndex frame_id_hand = 0;

    if (!pin_initialized && !pin_init_failed)
    {
      try
      {
        // ===================== URDF 路径 =====================
        // upperlimb_robot/urdf/left_arm.urdf
        //
        std::string urdf_path =
            ament_index_cpp::get_package_share_directory("upperlimb_robot") +
            "/urdf/left_arm.urdf";

        // ===================== 加载 URDF =====================
        //
        // joint1~3 已改成 revolute，joint8~10 保持 fixed，
        // model 里应有 joint1~7 这 7 个可动关节
        //
        pinocchio::urdf::buildModel(urdf_path, model);
        data = std::make_unique<pinocchio::Data>(model);

        // ===================== 获取两个六维力传感器 frame =====================
        //
        // ft_sensor_frame     -> 大臂绑缚件
        // ft_sensor_frame_2   -> 手部绑缚件
        //
        frame_id_arm = model.getFrameId("ft_sensor_frame");
        frame_id_hand = model.getFrameId("ft_sensor_frame_2");

        if (frame_id_arm >= model.frames.size())
        {
          std::cerr << "[runZeroForceMode] 没找到 frame: ft_sensor_frame" << std::endl;
          pin_init_failed = true;
        }
        else if (frame_id_hand >= model.frames.size())
        {
          std::cerr << "[runZeroForceMode] 没找到 frame: ft_sensor_frame_2" << std::endl;
          pin_init_failed = true;
        }
        else if (model.nq != 7 || model.nv != 7)
        {
          std::cerr
              << "[runZeroForceMode] 当前 Pinocchio 模型自由度不是 7，"
              << "请确认 joint1~3 已改成 revolute，joint8~10 保持 fixed。"
              << " model.nq=" << model.nq << " model.nv=" << model.nv
              << std::endl;
          pin_init_failed = true;
        }
        else
        {
          pin_initialized = true;
          std::cout
              << "[runZeroForceMode] Pinocchio 初始化成功。"
              << " urdf_path=" << urdf_path
              << " nq=" << model.nq
              << " nv=" << model.nv
              << std::endl;
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "[runZeroForceMode] Pinocchio 初始化异常: " << e.what() << std::endl;
        pin_init_failed = true;
      }
    }

    if (!pin_initialized || pin_init_failed || !data)
    {
      // 初始化失败则本轮不输出
      output.valid = false;
      return;
    }

    // ===================== 传感器有效性检查 =====================
    //
    // 当前传感器无效时，不要输出扭矩。
    //
    if (!sensor_state.valid)
    {
      output.valid = false;
      return;
    }

    // ===================== 组装 q / dq =====================
    //
    // 1. state.position / velocity 的单位是 deg / deg/s
    // 2. Pinocchio 这里使用 rad / rad/s
    // 3. 当前模型自由度为 7：
    //    q = [joint1, joint2, joint3, joint4, joint5, joint6, joint7]
    //
    constexpr double DEG2RAD = M_PI / 180.0;

    Eigen::VectorXd q = Eigen::VectorXd::Zero(model.nq);
    Eigen::VectorXd v = Eigen::VectorXd::Zero(model.nv);

    q(0) = state.position[IDX_J1] * DEG2RAD;
    q(1) = state.position[IDX_J2] * DEG2RAD;
    q(2) = state.position[IDX_J3] * DEG2RAD;
    q(3) = state.position[IDX_J4] * DEG2RAD;
    q(4) = state.position[IDX_J5] * DEG2RAD;
    q(5) = state.position[IDX_J6] * DEG2RAD;
    q(6) = state.position[IDX_J7] * DEG2RAD;

    v(0) = state.velocity[IDX_J1] * DEG2RAD;
    v(1) = state.velocity[IDX_J2] * DEG2RAD;
    v(2) = state.velocity[IDX_J3] * DEG2RAD;
    v(3) = state.velocity[IDX_J4] * DEG2RAD;
    v(4) = state.velocity[IDX_J5] * DEG2RAD;
    v(5) = state.velocity[IDX_J6] * DEG2RAD;
    v(6) = state.velocity[IDX_J7] * DEG2RAD;

    // ===================== 读取并去偏两个六维力传感器 =====================
    //
    // 左臂：
    // SENSOR_LEFT_HAND = 2
    // SENSOR_LEFT_ARM  = 3
    //
    // 约定：
    // 1. sensor_state.sensor[] 是实时值
    // 2. sensor_state.bias[]   是进入零力模式时记录的零偏
    // 3. 这里直接做 raw - bias
    //
    const auto &raw_hand = sensor_state.sensor[SENSOR_LEFT_HAND];
    const auto &bias_hand = sensor_state.bias[SENSOR_LEFT_HAND];

    const auto &raw_arm = sensor_state.sensor[SENSOR_LEFT_ARM];
    const auto &bias_arm = sensor_state.bias[SENSOR_LEFT_ARM];

    double fx_arm = raw_arm.fx - bias_arm.fx;
    double fy_arm = raw_arm.fy - bias_arm.fy;
    double fz_arm = raw_arm.fz - bias_arm.fz;
    double mx_arm = raw_arm.mx - bias_arm.mx;
    double my_arm = raw_arm.my - bias_arm.my;
    double mz_arm = raw_arm.mz - bias_arm.mz;

    double fx_hand = raw_hand.fx - bias_hand.fx;
    double fy_hand = raw_hand.fy - bias_hand.fy;
    double fz_hand = raw_hand.fz - bias_hand.fz;
    double mx_hand = raw_hand.mx - bias_hand.mx;
    double my_hand = raw_hand.my - bias_hand.my;
    double mz_hand = raw_hand.mz - bias_hand.mz;

    // ===================== 传感器方向符号修正 =====================
    //
    // 顺序：
    // [Fx, Fy, Fz, Mx, My, Mz]
    //
    static const std::array<double, 6> arm_sign = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0};

    static const std::array<double, 6> hand_sign = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0};

    fx_arm *= arm_sign[0];
    fy_arm *= arm_sign[1];
    fz_arm *= arm_sign[2];
    mx_arm *= arm_sign[3];
    my_arm *= arm_sign[4];
    mz_arm *= arm_sign[5];

    fx_hand *= hand_sign[0];
    fy_hand *= hand_sign[1];
    fz_hand *= hand_sign[2];
    mx_hand *= hand_sign[3];
    my_hand *= hand_sign[4];
    mz_hand *= hand_sign[5];

    // ===================== 死区 =====================
    //
    // 力 / 力矩很小时直接置 0，防止噪声抖动。
    //
    const double force_deadzone = 1.0;   // N
    const double torque_deadzone = 0.05; // Nm

    auto apply_deadzone = [](double x, double dz) -> double
    {
      return (std::abs(x) < dz) ? 0.0 : x;
    };

    fx_arm = apply_deadzone(fx_arm, force_deadzone);
    fy_arm = apply_deadzone(fy_arm, force_deadzone);
    fz_arm = apply_deadzone(fz_arm, force_deadzone);
    mx_arm = apply_deadzone(mx_arm, torque_deadzone);
    my_arm = apply_deadzone(my_arm, torque_deadzone);
    mz_arm = apply_deadzone(mz_arm, torque_deadzone);

    fx_hand = apply_deadzone(fx_hand, force_deadzone);
    fy_hand = apply_deadzone(fy_hand, force_deadzone);
    fz_hand = apply_deadzone(fz_hand, force_deadzone);
    mx_hand = apply_deadzone(mx_hand, torque_deadzone);
    my_hand = apply_deadzone(my_hand, torque_deadzone);
    mz_hand = apply_deadzone(mz_hand, torque_deadzone);

    // ===================== 限幅 =====================
    //
    // 防止异常值把控制打飞。
    //
    const double force_limit = 80.0; // N
    const double moment_limit = 8.0; // Nm

    auto clamp_abs = [](double x, double lim) -> double
    {
      if (x > lim)
        return lim;
      if (x < -lim)
        return -lim;
      return x;
    };

    fx_arm = clamp_abs(fx_arm, force_limit);
    fy_arm = clamp_abs(fy_arm, force_limit);
    fz_arm = clamp_abs(fz_arm, force_limit);
    mx_arm = clamp_abs(mx_arm, moment_limit);
    my_arm = clamp_abs(my_arm, moment_limit);
    mz_arm = clamp_abs(mz_arm, moment_limit);

    fx_hand = clamp_abs(fx_hand, force_limit);
    fy_hand = clamp_abs(fy_hand, force_limit);
    fz_hand = clamp_abs(fz_hand, force_limit);
    mx_hand = clamp_abs(mx_hand, moment_limit);
    my_hand = clamp_abs(my_hand, moment_limit);
    mz_hand = clamp_abs(mz_hand, moment_limit);

    // ===================== 计算重力项 =====================
    //
    // g(q) 的维度是 7，对应 joint1~7。
    // Eigen::VectorXd g 本质上就是一个：动态大小的一维向量（列向量），里面存的是每个关节的重力力矩
    // computeGeneralizedGravity:
    //     model → 机器人结构 + 质量
    //     data  → 中间缓存
    //     q     → 当前关节角（rad）
    //     g(q)  → 每个关节的重力力矩
    Eigen::VectorXd g = pinocchio::computeGeneralizedGravity(model, *data, q);
    applyArmGravityCompensation(
        g, SINGLE_ARM_V_IDS, LEFT_ARM_GRAVITY_COMPENSATION);
    addArmFrictionCompensation(
        g, v, SINGLE_ARM_V_IDS, LEFT_ARM_FRICTION_COMPENSATION);

    // ===================== 计算两个传感器 frame 的 Jacobian =====================
    //
    // 把“末端（传感器）空间的力/速度”映射到“关节空间”
    //
    // 创建两个大小为 6 × nv 的矩阵，并全部初始化为 0
    // 为什么是 6 行？
    // [ vx ]   ← 线速度 x
    // [ vy ]
    // [ vz ]
    // [ wx ]   ← 角速度 x
    // [ wy ]
    // [ wz ]
    // 为什么是 nv 列？
    // nv 是模型的自由度数量，这里是 7，对应 joint1~7。
    Eigen::MatrixXd J_arm = Eigen::MatrixXd::Zero(6, model.nv);
    Eigen::MatrixXd J_hand = Eigen::MatrixXd::Zero(6, model.nv);

    pinocchio::computeFrameJacobian(model, *data, q, frame_id_arm, pinocchio::LOCAL, J_arm);
    pinocchio::computeFrameJacobian(model, *data, q, frame_id_hand, pinocchio::LOCAL, J_hand);

    // ===================== 构造 Pinocchio 空间力 =====================
    //
    // Pinocchio 空间力的顺序是：
    // [angular; linear]
    //
    // 直接用 Force 对象，最后 toVector()，避免顺序写错。

    // 创建一个 空间力（Force）对象 f_arm，并初始化为零
    pinocchio::Force f_arm = pinocchio::Force::Zero();
    // 把 fx_arm、fy_arm、fz_arm 填入 f_arm 的线性部分，把 mx_arm、my_arm、mz_arm 填入 f_arm 的角部分
    f_arm.linear() << fx_arm, fy_arm, fz_arm;
    f_arm.angular() << mx_arm, my_arm, mz_arm;

    pinocchio::Force f_hand = pinocchio::Force::Zero();
    f_hand.linear() << fx_hand, fy_hand, fz_hand;
    f_hand.angular() << mx_hand, my_hand, mz_hand;

    // ===================== 外力映射到关节扭矩 =====================
    //
    // 数学意义:τ=J^T*F
    // tau_ext = J_arm^T * F_arm + J_hand^T * F_hand
    //
    Eigen::VectorXd tau_arm = J_arm.transpose() * f_arm.toVector();
    Eigen::VectorXd tau_hand = J_hand.transpose() * f_hand.toVector();

    Eigen::VectorXd tau_ext = tau_arm + tau_hand;

    // ===================== 关节阻尼项 =====================
    //
    // 防止零力模式下出现漂、轻微自激或关节发飘。
    //
    // 创建一个长度为 nv 的向量：
    Eigen::VectorXd damping = Eigen::VectorXd::Zero(model.nv);

    // 给每个关节设置阻尼系数：
    // 背部零力不是“完全无阻尼”，而是“有一定粘滞感，但不会死硬”
    // 肩部和肘部继续保留较强跟随性
    damping(0) = 0.0;
    damping(1) = 0.4;
    damping(2) = 0.3;
    damping(3) = 0.0;
    damping(4) = 0.0;
    damping(5) = 0.2;
    damping(6) = 0.3;

    // 计算阻尼力矩：tau_damping = -damping * v，反速度方向
    // damping.asDiagonal()
    // 把向量变成对角矩阵，再乘 v，就相当于每个元素分别乘以对应的速度
    Eigen::VectorXd tau_damping = -(damping.asDiagonal() * v);

    // ===================== 最终关节扭矩 =====================
    //
    // 当前采用：
    // tau = g(q) + tau_ext + tau_damping
    //
    // 如果方向整体反了，
    // 优先检查：
    // 1. 传感器符号 arm_sign / hand_sign
    // 2. 电机 torque raw 映射方向
    //
    Eigen::VectorXd tau = g + tau_ext + tau_damping;

    // ===================== 最终扭矩限幅 =====================
    //
    // 输出给执行层前，限制每个关节的目标扭矩。
    //
    const double joint_torque_limit_j1 = 30.0;
    const double joint_torque_limit_j2 = 20.0;
    const double joint_torque_limit_j3 = 16.0;
    const double joint_torque_limit_j4 = 12.0;
    const double joint_torque_limit_j5 = 12.0;
    const double joint_torque_limit_j6 = 12.0;
    const double joint_torque_limit_j7 = 8.0;

    tau(0) = clamp_abs(tau(0), joint_torque_limit_j1);
    tau(1) = clamp_abs(tau(1), joint_torque_limit_j2);
    tau(2) = clamp_abs(tau(2), joint_torque_limit_j3);
    tau(3) = clamp_abs(tau(3), joint_torque_limit_j4);
    tau(4) = clamp_abs(tau(4), joint_torque_limit_j5);
    tau(5) = clamp_abs(tau(5), joint_torque_limit_j6);
    tau(6) = clamp_abs(tau(6), joint_torque_limit_j7);

    // ===================== 输出到控制层 =====================
    //
    // 这里对 joint1~7 对应的控制层索引写扭矩。
    // 其他关节默认保持 0，不参与零力控制。
    //
    output.use_torque[IDX_J1] = true;
    output.use_torque[IDX_J2] = true;
    output.use_torque[IDX_J3] = true;
    output.use_torque[IDX_J4] = true;
    output.use_torque[IDX_J5] = true;
    output.use_torque[IDX_J6] = true;
    output.use_torque[IDX_J7] = true;

    output.target_torque[IDX_J1] = tau(0);
    output.target_torque[IDX_J2] = tau(1);
    output.target_torque[IDX_J3] = tau(2);
    output.target_torque[IDX_J4] = tau(3);
    output.target_torque[IDX_J5] = tau(4);
    output.target_torque[IDX_J6] = tau(5);
    output.target_torque[IDX_J7] = tau(6);

    // 末端其余关节固定，避免切模式后还能晃动
    output.use_position[17] = true;
    output.target_position[17] = 0.0;
    output.target_velocity[17] = pulsePerMsToJointSpeedDegPerSecMagnitude(18, 1500.0);
    output.target_acc[17] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 5.0);
    output.target_dec[17] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 0.25);
    output.target_smooth_time[17] = 25;

    output.use_position[18] = true;
    output.target_position[18] = 0.0;
    output.target_velocity[18] = pulsePerMsToJointSpeedDegPerSecMagnitude(19, 1500.0);
    output.target_acc[18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 5.0);
    output.target_dec[18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 0.25);
    output.target_smooth_time[18] = 25;

    output.use_position[19] = true;
    output.target_position[19] = 0.0;
    output.target_velocity[19] = pulsePerMsToJointSpeedDegPerSecMagnitude(20, 1500.0);
    output.target_acc[19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 5.0);
    output.target_dec[19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 0.25);
    output.target_smooth_time[19] = 25;

    // ===================== 输出有效 =====================
    output.valid = true;
  }

  // ===================== 右臂零力模式 =====================
  void runRightZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output)
  {
    // ===================== 输出初始化 =====================
    //
    // 每次进入先清空 output，
    // 然后只对右臂需要控制的关节写入输出。
    //
    output = ControlOutputCache{};
    output.valid = false;

    // ===================== 右臂 joint11~joint20 的控制层索引 =====================
    //
    // 当前默认约定：
    // 右臂控制层索引 0~9
    //
    // joint11 ~ joint17 : 可动关节
    // joint18 ~ joint20 : 固定末端
    //
    constexpr std::size_t IDX_J11 = 0;
    constexpr std::size_t IDX_J12 = 1;
    constexpr std::size_t IDX_J13 = 2;
    constexpr std::size_t IDX_J14 = 3;
    constexpr std::size_t IDX_J15 = 4;
    constexpr std::size_t IDX_J16 = 5;
    constexpr std::size_t IDX_J17 = 6;
    // joint18~joint20 当前在执行层作为非控制末端轴过滤，
    // 本函数内不再持续下发位置保持，因此不定义 IDX_J18~IDX_J20。

    // ===================== Pinocchio 懒加载上下文 =====================
    //
    // 第一次进入时加载右臂 URDF、查 frame id；
    // 后续周期只做实时计算。
    //
    static bool pin_initialized = false;
    static bool pin_init_failed = false;
    static pinocchio::Model model;
    static std::unique_ptr<pinocchio::Data> data;
    static pinocchio::FrameIndex frame_id_arm = 0;
    static pinocchio::FrameIndex frame_id_hand = 0;

    if (!pin_initialized && !pin_init_failed)
    {
      try
      {
        // ===================== URDF 路径 =====================
        //
        // upperlimb_robot/urdf/right_arm.urdf
        //
        std::string urdf_path =
            ament_index_cpp::get_package_share_directory("upperlimb_robot") +
            "/urdf/right_arm.urdf";

        // ===================== 加载 URDF =====================
        //
        // 当前右臂模型约定：
        // joint11~joint17 为 revolute
        // joint18~joint20 为 fixed
        //
        pinocchio::urdf::buildModel(urdf_path, model);
        data = std::make_unique<pinocchio::Data>(model);

        // ===================== 获取两个六维力传感器 frame =====================
        //
        // ft_rightsensor_frame     -> 大臂绑缚件
        // ft_rightsensor_frame_2   -> 手部绑缚件
        //
        frame_id_arm = model.getFrameId("ft_rightsensor_frame");
        frame_id_hand = model.getFrameId("ft_rightsensor_frame_2");

        if (frame_id_arm >= model.frames.size())
        {
          std::cerr << "[runRightZeroForceMode] 没找到 frame: ft_rightsensor_frame" << std::endl;
          pin_init_failed = true;
        }
        else if (frame_id_hand >= model.frames.size())
        {
          std::cerr << "[runRightZeroForceMode] 没找到 frame: ft_rightsensor_frame_2" << std::endl;
          pin_init_failed = true;
        }
        else if (model.nq != 7 || model.nv != 7)
        {
          std::cerr
              << "[runRightZeroForceMode] 当前 Pinocchio 模型自由度不是 7，"
              << "请确认 right_arm.urdf 中 joint11~joint17 为 revolute，"
              << "joint18~joint20 为 fixed。"
              << " model.nq=" << model.nq
              << " model.nv=" << model.nv
              << std::endl;
          pin_init_failed = true;
        }
        else
        {
          pin_initialized = true;
          std::cout
              << "[runRightZeroForceMode] Pinocchio 初始化成功。"
              << " urdf_path=" << urdf_path
              << " nq=" << model.nq
              << " nv=" << model.nv
              << std::endl;
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "[runRightZeroForceMode] Pinocchio 初始化异常: " << e.what() << std::endl;
        pin_init_failed = true;
      }
    }

    if (!pin_initialized || pin_init_failed || !data)
    {
      output.valid = false;
      return;
    }

    // ===================== 传感器有效性检查 =====================
    //
    // 当前传感器无效时，不输出扭矩。
    //
    if (!sensor_state.valid)
    {
      output.valid = false;
      return;
    }

    // ===================== 组装 q / v =====================
    //
    // 注意：
    // 1. state.position / velocity 的单位是 deg / deg/s
    // 2. Pinocchio 这里使用 rad / rad/s
    // 3. 当前右臂模型自由度为 7：
    //    q = [joint11, joint12, joint13, joint14, joint15, joint16, joint17]
    //
    constexpr double DEG2RAD = M_PI / 180.0;

    Eigen::VectorXd q = Eigen::VectorXd::Zero(model.nq);
    Eigen::VectorXd v = Eigen::VectorXd::Zero(model.nv);

    q(0) = state.position[IDX_J11] * DEG2RAD;
    q(1) = state.position[IDX_J12] * DEG2RAD;
    q(2) = state.position[IDX_J13] * DEG2RAD;
    q(3) = state.position[IDX_J14] * DEG2RAD;
    q(4) = state.position[IDX_J15] * DEG2RAD;
    q(5) = state.position[IDX_J16] * DEG2RAD;
    q(6) = state.position[IDX_J17] * DEG2RAD;

    v(0) = state.velocity[IDX_J11] * DEG2RAD;
    v(1) = state.velocity[IDX_J12] * DEG2RAD;
    v(2) = state.velocity[IDX_J13] * DEG2RAD;
    v(3) = state.velocity[IDX_J14] * DEG2RAD;
    v(4) = state.velocity[IDX_J15] * DEG2RAD;
    v(5) = state.velocity[IDX_J16] * DEG2RAD;
    v(6) = state.velocity[IDX_J17] * DEG2RAD;

    // ===================== 读取并去偏两个六维力传感器 =====================
    //
    // 右臂：
    // SENSOR_RIGHT_HAND = 0
    // SENSOR_RIGHT_ARM  = 1
    //
    const auto &raw_hand = sensor_state.sensor[SENSOR_RIGHT_HAND];
    const auto &bias_hand = sensor_state.bias[SENSOR_RIGHT_HAND];

    const auto &raw_arm = sensor_state.sensor[SENSOR_RIGHT_ARM];
    const auto &bias_arm = sensor_state.bias[SENSOR_RIGHT_ARM];

    double fx_arm = raw_arm.fx - bias_arm.fx;
    double fy_arm = raw_arm.fy - bias_arm.fy;
    double fz_arm = raw_arm.fz - bias_arm.fz;
    double mx_arm = raw_arm.mx - bias_arm.mx;
    double my_arm = raw_arm.my - bias_arm.my;
    double mz_arm = raw_arm.mz - bias_arm.mz;

    double fx_hand = raw_hand.fx - bias_hand.fx;
    double fy_hand = raw_hand.fy - bias_hand.fy;
    double fz_hand = raw_hand.fz - bias_hand.fz;
    double mx_hand = raw_hand.mx - bias_hand.mx;
    double my_hand = raw_hand.my - bias_hand.my;
    double mz_hand = raw_hand.mz - bias_hand.mz;

    // ===================== 传感器方向符号修正 =====================
    //
    // 顺序：
    // [Fx, Fy, Fz, Mx, My, Mz]
    //
    // 这里先默认全 1。
    // 如果右臂实机方向出现“人往前推，机械臂反而更顶住”的情况，
    // 优先先改这里。
    //
    static const std::array<double, 6> arm_sign = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0};

    static const std::array<double, 6> hand_sign = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0};

    fx_arm *= arm_sign[0];
    fy_arm *= arm_sign[1];
    fz_arm *= arm_sign[2];
    mx_arm *= arm_sign[3];
    my_arm *= arm_sign[4];
    mz_arm *= arm_sign[5];

    fx_hand *= hand_sign[0];
    fy_hand *= hand_sign[1];
    fz_hand *= hand_sign[2];
    mx_hand *= hand_sign[3];
    my_hand *= hand_sign[4];
    mz_hand *= hand_sign[5];

    // ===================== 死区 =====================
    //
    // 力 / 力矩很小时直接置 0，防止噪声抖动。
    //
    const double force_deadzone = 1.0;   // N
    const double torque_deadzone = 0.05; // Nm

    auto apply_deadzone = [](double x, double dz) -> double
    {
      return (std::abs(x) < dz) ? 0.0 : x;
    };

    fx_arm = apply_deadzone(fx_arm, force_deadzone);
    fy_arm = apply_deadzone(fy_arm, force_deadzone);
    fz_arm = apply_deadzone(fz_arm, force_deadzone);
    mx_arm = apply_deadzone(mx_arm, torque_deadzone);
    my_arm = apply_deadzone(my_arm, torque_deadzone);
    mz_arm = apply_deadzone(mz_arm, torque_deadzone);

    fx_hand = apply_deadzone(fx_hand, force_deadzone);
    fy_hand = apply_deadzone(fy_hand, force_deadzone);
    fz_hand = apply_deadzone(fz_hand, force_deadzone);
    mx_hand = apply_deadzone(mx_hand, torque_deadzone);
    my_hand = apply_deadzone(my_hand, torque_deadzone);
    mz_hand = apply_deadzone(mz_hand, torque_deadzone);

    // ===================== 限幅 =====================
    //
    // 防止异常值把控制打飞。
    //
    const double force_limit = 80.0; // N
    const double moment_limit = 8.0; // Nm

    auto clamp_abs = [](double x, double lim) -> double
    {
      if (x > lim)
        return lim;
      if (x < -lim)
        return -lim;
      return x;
    };

    fx_arm = clamp_abs(fx_arm, force_limit);
    fy_arm = clamp_abs(fy_arm, force_limit);
    fz_arm = clamp_abs(fz_arm, force_limit);
    mx_arm = clamp_abs(mx_arm, moment_limit);
    my_arm = clamp_abs(my_arm, moment_limit);
    mz_arm = clamp_abs(mz_arm, moment_limit);

    fx_hand = clamp_abs(fx_hand, force_limit);
    fy_hand = clamp_abs(fy_hand, force_limit);
    fz_hand = clamp_abs(fz_hand, force_limit);
    mx_hand = clamp_abs(mx_hand, moment_limit);
    my_hand = clamp_abs(my_hand, moment_limit);
    mz_hand = clamp_abs(mz_hand, moment_limit);

    // ===================== 计算重力项 =====================
    //
    // g(q) 对应 joint11~joint17 的重力补偿力矩
    //
    Eigen::VectorXd g = pinocchio::computeGeneralizedGravity(model, *data, q);
    applyArmGravityCompensation(
        g, SINGLE_ARM_V_IDS, RIGHT_ARM_GRAVITY_COMPENSATION);
    addArmFrictionCompensation(
        g, v, SINGLE_ARM_V_IDS, RIGHT_ARM_FRICTION_COMPENSATION);

    // ===================== 计算两个传感器 frame 的 Jacobian =====================
    //
    Eigen::MatrixXd J_arm = Eigen::MatrixXd::Zero(6, model.nv);
    Eigen::MatrixXd J_hand = Eigen::MatrixXd::Zero(6, model.nv);

    pinocchio::computeFrameJacobian(model, *data, q, frame_id_arm, pinocchio::LOCAL, J_arm);
    pinocchio::computeFrameJacobian(model, *data, q, frame_id_hand, pinocchio::LOCAL, J_hand);

    // ===================== 构造 Pinocchio 空间力 =====================
    //
    // Force 顺序是 [angular; linear]
    //
    pinocchio::Force f_arm = pinocchio::Force::Zero();
    f_arm.linear() << fx_arm, fy_arm, fz_arm;
    f_arm.angular() << mx_arm, my_arm, mz_arm;

    pinocchio::Force f_hand = pinocchio::Force::Zero();
    f_hand.linear() << fx_hand, fy_hand, fz_hand;
    f_hand.angular() << mx_hand, my_hand, mz_hand;

    // ===================== 外力映射到关节扭矩 =====================
    //
    // tau_ext = J_arm^T * F_arm + J_hand^T * F_hand
    //
    Eigen::VectorXd tau_arm = J_arm.transpose() * f_arm.toVector();
    Eigen::VectorXd tau_hand = J_hand.transpose() * f_hand.toVector();
    Eigen::VectorXd tau_ext = tau_arm + tau_hand;

    // ===================== 关节阻尼项 =====================
    //
    // 防止零力模式下出现漂、轻微自激或关节发飘。
    //
    Eigen::VectorXd damping = Eigen::VectorXd::Zero(model.nv);

    // 先直接沿用左臂这套阻尼配置
    damping(0) = 0.0;
    damping(1) = 0.4;
    damping(2) = 0.3;
    damping(3) = 0.0;
    damping(4) = 0.0;
    damping(5) = 0.2;
    damping(6) = 0.3;

    Eigen::VectorXd tau_damping = -(damping.asDiagonal() * v);

    // ===================== 最终关节扭矩 =====================
    //
    // tau = g(q) + tau_ext + tau_damping
    //
    Eigen::VectorXd tau = g + tau_ext + tau_damping;

    // ===================== 最终扭矩限幅 =====================
    //
    // 这里按右臂 joint11~joint17 依次限幅。
    //
    const double joint_torque_limit_j11 = 30.0;
    const double joint_torque_limit_j12 = 20.0;
    const double joint_torque_limit_j13 = 16.0;
    const double joint_torque_limit_j14 = 12.0;
    const double joint_torque_limit_j15 = 12.0;
    const double joint_torque_limit_j16 = 12.0;
    const double joint_torque_limit_j17 = 8.0;

    tau(0) = clamp_abs(-tau(0), joint_torque_limit_j11);
    tau(1) = clamp_abs(-tau(1), joint_torque_limit_j12);
    tau(2) = clamp_abs(-tau(2), joint_torque_limit_j13);
    tau(3) = clamp_abs(-tau(3), joint_torque_limit_j14);
    tau(4) = clamp_abs(-tau(4), joint_torque_limit_j15);
    tau(5) = clamp_abs(-tau(5), joint_torque_limit_j16);
    tau(6) = clamp_abs(-tau(6), joint_torque_limit_j17);

    // ===================== 输出到控制层 =====================
    //
    // joint11~joint17 走扭矩控制
    //
    output.use_torque[IDX_J11] = true;
    output.use_torque[IDX_J12] = true;
    output.use_torque[IDX_J13] = true;
    output.use_torque[IDX_J14] = true;
    output.use_torque[IDX_J15] = true;
    output.use_torque[IDX_J16] = true;
    output.use_torque[IDX_J17] = true;

    output.target_torque[IDX_J11] = tau(0);
    output.target_torque[IDX_J12] = tau(1);
    output.target_torque[IDX_J13] = tau(2);
    output.target_torque[IDX_J14] = tau(3);
    output.target_torque[IDX_J15] = tau(4);
    output.target_torque[IDX_J16] = tau(5);
    output.target_torque[IDX_J17] = tau(6);

    // ===================== 保存右臂零力模式扭矩到 CSV =====================
    static std::ofstream csv_file;
    static bool csv_initialized = false;
    static int log_count = 0;

    if (!csv_initialized)
    {
      csv_file.open("right_zero_force_tau_log.csv", std::ios::out | std::ios::app);

      if (csv_file.is_open())
      {
        csv_file << "wall_time,t,tau1,tau2,tau3,tau4,tau5,tau6,tau7\n";
        csv_initialized = true;
      }
      else
      {
        std::cerr << "[runRightZeroForceMode] 无法打开 right_zero_force_tau_log.csv" << std::endl;
      }
    }

    // 降采样记录，避免每个控制周期都写文件
    log_count++;

    if (csv_initialized && (log_count % 4 == 0))
    {
      static auto t0 = std::chrono::steady_clock::now();

      auto now_sys = std::chrono::system_clock::now();
      auto now_steady = std::chrono::steady_clock::now();

      double t =
          std::chrono::duration<double>(now_steady - t0).count();

      auto now_time_t = std::chrono::system_clock::to_time_t(now_sys);
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now_sys.time_since_epoch()) %
                1000;

      char time_str[64];
      std::strftime(
          time_str,
          sizeof(time_str),
          "%Y-%m-%d %H:%M:%S",
          std::localtime(&now_time_t));

      csv_file
          << time_str << "."
          << std::setw(3) << std::setfill('0') << ms.count() << ","
          << t << ","
          << tau(0) << ","
          << tau(1) << ","
          << tau(2) << ","
          << tau(3) << ","
          << tau(4) << ","
          << tau(5) << ","
          << tau(6) << "\n";
    }

    // ===================== 输出有效 =====================
    output.valid = true;
  }

  // ===================== 双侧零力模式 =====================
  void runBilateralZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output)
  {
    // ===================== 输出初始化 =====================
    output = ControlOutputCache{};
    output.valid = false;

    // ===================== 控制层索引约定 =====================
    //
    // 右臂：
    // joint11~joint20 -> 控制层索引 0~9
    //
    // 左臂：
    // joint1~joint10  -> 控制层索引 10~19
    //
    // 其中：
    // 右臂可动：joint11~joint17 -> 0~6
    // 右臂固定：joint18~joint20 -> 7~9
    //
    // 左臂可动：joint1~joint7   -> 10~16
    // 左臂固定：joint8~joint10  -> 17~19
    //
    constexpr std::size_t IDX_R_J11 = 0;
    constexpr std::size_t IDX_R_J12 = 1;
    constexpr std::size_t IDX_R_J13 = 2;
    constexpr std::size_t IDX_R_J14 = 3;
    constexpr std::size_t IDX_R_J15 = 4;
    constexpr std::size_t IDX_R_J16 = 5;
    constexpr std::size_t IDX_R_J17 = 6;
    constexpr std::size_t IDX_R_J18 = 7;
    constexpr std::size_t IDX_R_J19 = 8;
    constexpr std::size_t IDX_R_J20 = 9;

    constexpr std::size_t IDX_L_J1 = 10;
    constexpr std::size_t IDX_L_J2 = 11;
    constexpr std::size_t IDX_L_J3 = 12;
    constexpr std::size_t IDX_L_J4 = 13;
    constexpr std::size_t IDX_L_J5 = 14;
    constexpr std::size_t IDX_L_J6 = 15;
    constexpr std::size_t IDX_L_J7 = 16;
    constexpr std::size_t IDX_L_J8 = 17;
    constexpr std::size_t IDX_L_J9 = 18;
    constexpr std::size_t IDX_L_J10 = 19;

    // ===================== 双臂 Pinocchio 懒加载上下文 =====================
    //
    // 这里不再分别加载 left_arm.urdf 和 right_arm.urdf。
    // 双臂零力模式只加载一个双臂整体 URDF。
    //
    // URDF 要求：
    // 1. 左臂 joint1~joint7 为可动关节
    // 2. 右臂 joint11~joint17 为可动关节
    // 3. 左臂 joint8~joint10 固定
    // 4. 右臂 joint18~joint20 固定
    // 5. 模型总自由度 nq/nv 应为 14
    //
    static bool pin_initialized = false;
    static bool pin_init_failed = false;
    static pinocchio::Model model;
    static std::unique_ptr<pinocchio::Data> data;

    static pinocchio::FrameIndex left_frame_id_arm = 0;
    static pinocchio::FrameIndex left_frame_id_hand = 0;
    static pinocchio::FrameIndex right_frame_id_arm = 0;
    static pinocchio::FrameIndex right_frame_id_hand = 0;

    // 每个关节在 Pinocchio q/v 向量中的索引。
    // 不直接假定 URDF 中的关节顺序，避免双臂 URDF 排列变化后 q/v 对不上。
    static std::array<int, 7> left_q_id = {-1, -1, -1, -1, -1, -1, -1};
    static std::array<int, 7> left_v_id = {-1, -1, -1, -1, -1, -1, -1};
    static std::array<int, 7> right_q_id = {-1, -1, -1, -1, -1, -1, -1};
    static std::array<int, 7> right_v_id = {-1, -1, -1, -1, -1, -1, -1};

    if (!pin_initialized && !pin_init_failed)
    {
      try
      {
        // ===================== URDF 路径 =====================
        std::string urdf_path =
            ament_index_cpp::get_package_share_directory("upperlimb_robot") +
            "/urdf/robot_arms.urdf";

        pinocchio::urdf::buildModel(urdf_path, model);
        data = std::make_unique<pinocchio::Data>(model);

        left_frame_id_arm = model.getFrameId("ft_sensor_frame");
        left_frame_id_hand = model.getFrameId("ft_sensor_frame_2");
        right_frame_id_arm = model.getFrameId("ft_rightsensor_frame");
        right_frame_id_hand = model.getFrameId("ft_rightsensor_frame_2");

        auto load_joint_index = [&](const std::string &joint_name, int &q_id, int &v_id) -> bool
        {
          const pinocchio::JointIndex jid = model.getJointId(joint_name);

          if (jid >= model.joints.size())
          {
            std::cerr
                << "[runBilateralZeroForceMode] 双臂 URDF 没找到 joint: "
                << joint_name << std::endl;
            return false;
          }

          q_id = model.joints[jid].idx_q();
          v_id = model.joints[jid].idx_v();

          if (q_id < 0 || q_id >= model.nq || v_id < 0 || v_id >= model.nv)
          {
            std::cerr
                << "[runBilateralZeroForceMode] joint 索引非法: "
                << joint_name
                << " q_id=" << q_id
                << " v_id=" << v_id
                << " nq=" << model.nq
                << " nv=" << model.nv
                << std::endl;
            return false;
          }

          return true;
        };

        bool ok = true;

        ok = ok && load_joint_index("joint1", left_q_id[0], left_v_id[0]);
        ok = ok && load_joint_index("joint2", left_q_id[1], left_v_id[1]);
        ok = ok && load_joint_index("joint3", left_q_id[2], left_v_id[2]);
        ok = ok && load_joint_index("joint4", left_q_id[3], left_v_id[3]);
        ok = ok && load_joint_index("joint5", left_q_id[4], left_v_id[4]);
        ok = ok && load_joint_index("joint6", left_q_id[5], left_v_id[5]);
        ok = ok && load_joint_index("joint7", left_q_id[6], left_v_id[6]);

        ok = ok && load_joint_index("joint11", right_q_id[0], right_v_id[0]);
        ok = ok && load_joint_index("joint12", right_q_id[1], right_v_id[1]);
        ok = ok && load_joint_index("joint13", right_q_id[2], right_v_id[2]);
        ok = ok && load_joint_index("joint14", right_q_id[3], right_v_id[3]);
        ok = ok && load_joint_index("joint15", right_q_id[4], right_v_id[4]);
        ok = ok && load_joint_index("joint16", right_q_id[5], right_v_id[5]);
        ok = ok && load_joint_index("joint17", right_q_id[6], right_v_id[6]);

        if (left_frame_id_arm >= model.frames.size())
        {
          std::cerr << "[runBilateralZeroForceMode] 双臂 URDF 没找到 frame: ft_sensor_frame" << std::endl;
          pin_init_failed = true;
        }
        else if (left_frame_id_hand >= model.frames.size())
        {
          std::cerr << "[runBilateralZeroForceMode] 双臂 URDF 没找到 frame: ft_sensor_frame_2" << std::endl;
          pin_init_failed = true;
        }
        else if (right_frame_id_arm >= model.frames.size())
        {
          std::cerr << "[runBilateralZeroForceMode] 双臂 URDF 没找到 frame: ft_rightsensor_frame" << std::endl;
          pin_init_failed = true;
        }
        else if (right_frame_id_hand >= model.frames.size())
        {
          std::cerr << "[runBilateralZeroForceMode] 双臂 URDF 没找到 frame: ft_rightsensor_frame_2" << std::endl;
          pin_init_failed = true;
        }
        else if (!ok)
        {
          pin_init_failed = true;
        }
        else if (model.nq != 14 || model.nv != 14)
        {
          std::cerr
              << "[runBilateralZeroForceMode] 双臂整体模型自由度不是 14。"
              << "请确认 joint1~joint7、joint11~joint17 为可动关节，"
              << "joint8~joint10、joint18~joint20 为 fixed。"
              << " nq=" << model.nq
              << " nv=" << model.nv
              << std::endl;
          pin_init_failed = true;
        }
        else
        {
          pin_initialized = true;
          std::cout
              << "[runBilateralZeroForceMode] 双臂整体 Pinocchio 初始化成功。"
              << " urdf_path=" << urdf_path
              << " nq=" << model.nq
              << " nv=" << model.nv
              << std::endl;
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "[runBilateralZeroForceMode] 双臂 Pinocchio 初始化异常: " << e.what() << std::endl;
        pin_init_failed = true;
      }
    }

    if (!pin_initialized || pin_init_failed || !data)
    {
      output.valid = false;
      return;
    }

    // ===================== 传感器有效性检查 =====================
    if (!sensor_state.valid)
    {
      output.valid = false;
      return;
    }

    constexpr double DEG2RAD = M_PI / 180.0;

    const std::array<std::size_t, 7> left_ctrl_id = {
        IDX_L_J1, IDX_L_J2, IDX_L_J3, IDX_L_J4, IDX_L_J5, IDX_L_J6, IDX_L_J7};

    const std::array<std::size_t, 7> right_ctrl_id = {
        IDX_R_J11, IDX_R_J12, IDX_R_J13, IDX_R_J14, IDX_R_J15, IDX_R_J16, IDX_R_J17};

    // ===================== 组装双臂整体 q / v =====================
    //
    // q / v 是双臂整体模型的状态向量，不再拆成 q_left / q_right。
    //
    Eigen::VectorXd q = Eigen::VectorXd::Zero(model.nq);
    Eigen::VectorXd v = Eigen::VectorXd::Zero(model.nv);

    for (std::size_t i = 0; i < 7; ++i)
    {
      q(left_q_id[i]) = state.position[left_ctrl_id[i]] * DEG2RAD;
      v(left_v_id[i]) = state.velocity[left_ctrl_id[i]] * DEG2RAD;

      q(right_q_id[i]) = state.position[right_ctrl_id[i]] * DEG2RAD;
      v(right_v_id[i]) = state.velocity[right_ctrl_id[i]] * DEG2RAD;
    }

    // ===================== Wrench 读取、符号修正、死区、限幅 =====================
    struct Wrench6
    {
      double fx;
      double fy;
      double fz;
      double mx;
      double my;
      double mz;
    };

    auto read_wrench = [&](int sensor_id) -> Wrench6
    {
      const auto &raw = sensor_state.sensor[sensor_id];
      const auto &bias = sensor_state.bias[sensor_id];

      return {
          raw.fx - bias.fx,
          raw.fy - bias.fy,
          raw.fz - bias.fz,
          raw.mx - bias.mx,
          raw.my - bias.my,
          raw.mz - bias.mz};
    };

    Wrench6 left_arm = read_wrench(SENSOR_LEFT_ARM);
    Wrench6 left_hand = read_wrench(SENSOR_LEFT_HAND);
    Wrench6 right_arm = read_wrench(SENSOR_RIGHT_ARM);
    Wrench6 right_hand = read_wrench(SENSOR_RIGHT_HAND);

    // 顺序：[Fx, Fy, Fz, Mx, My, Mz]
    // 如果实机出现方向反了，优先改这里。
    static const std::array<double, 6> left_arm_sign = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    static const std::array<double, 6> left_hand_sign = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    static const std::array<double, 6> right_arm_sign = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    static const std::array<double, 6> right_hand_sign = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    auto apply_sign = [](Wrench6 &w, const std::array<double, 6> &sign)
    {
      w.fx *= sign[0];
      w.fy *= sign[1];
      w.fz *= sign[2];
      w.mx *= sign[3];
      w.my *= sign[4];
      w.mz *= sign[5];
    };

    apply_sign(left_arm, left_arm_sign);
    apply_sign(left_hand, left_hand_sign);
    apply_sign(right_arm, right_arm_sign);
    apply_sign(right_hand, right_hand_sign);

    const double force_deadzone = 1.0;   // N
    const double torque_deadzone = 0.05; // Nm

    auto apply_deadzone = [](double x, double dz) -> double
    {
      return (std::abs(x) < dz) ? 0.0 : x;
    };

    auto apply_wrench_deadzone = [&](Wrench6 &w)
    {
      w.fx = apply_deadzone(w.fx, force_deadzone);
      w.fy = apply_deadzone(w.fy, force_deadzone);
      w.fz = apply_deadzone(w.fz, force_deadzone);

      w.mx = apply_deadzone(w.mx, torque_deadzone);
      w.my = apply_deadzone(w.my, torque_deadzone);
      w.mz = apply_deadzone(w.mz, torque_deadzone);
    };

    apply_wrench_deadzone(left_arm);
    apply_wrench_deadzone(left_hand);
    apply_wrench_deadzone(right_arm);
    apply_wrench_deadzone(right_hand);

    const double force_limit = 80.0; // N
    const double moment_limit = 8.0; // Nm

    auto clamp_abs = [](double x, double lim) -> double
    {
      if (x > lim)
        return lim;
      if (x < -lim)
        return -lim;
      return x;
    };

    auto clamp_wrench = [&](Wrench6 &w)
    {
      w.fx = clamp_abs(w.fx, force_limit);
      w.fy = clamp_abs(w.fy, force_limit);
      w.fz = clamp_abs(w.fz, force_limit);

      w.mx = clamp_abs(w.mx, moment_limit);
      w.my = clamp_abs(w.my, moment_limit);
      w.mz = clamp_abs(w.mz, moment_limit);
    };

    clamp_wrench(left_arm);
    clamp_wrench(left_hand);
    clamp_wrench(right_arm);
    clamp_wrench(right_hand);

    // ===================== 双臂整体动力学计算 =====================
    //
    // g 的维度为 14，对应双臂整体模型的全部可动关节。
    // 这一步是和以前分开算 left_model/right_model 的本质区别。
    //
    Eigen::VectorXd g = pinocchio::computeGeneralizedGravity(model, *data, q);
    applyArmGravityCompensation(
        g, left_v_id, LEFT_ARM_GRAVITY_COMPENSATION);
    applyArmGravityCompensation(
        g, right_v_id, RIGHT_ARM_GRAVITY_COMPENSATION);
    addArmFrictionCompensation(
        g, v, left_v_id, LEFT_ARM_FRICTION_COMPENSATION);
    addArmFrictionCompensation(
        g, v, right_v_id, RIGHT_ARM_FRICTION_COMPENSATION);

    Eigen::MatrixXd J_left_arm = Eigen::MatrixXd::Zero(6, model.nv);
    Eigen::MatrixXd J_left_hand = Eigen::MatrixXd::Zero(6, model.nv);
    Eigen::MatrixXd J_right_arm = Eigen::MatrixXd::Zero(6, model.nv);
    Eigen::MatrixXd J_right_hand = Eigen::MatrixXd::Zero(6, model.nv);

    pinocchio::computeFrameJacobian(model, *data, q, left_frame_id_arm, pinocchio::LOCAL, J_left_arm);
    pinocchio::computeFrameJacobian(model, *data, q, left_frame_id_hand, pinocchio::LOCAL, J_left_hand);
    pinocchio::computeFrameJacobian(model, *data, q, right_frame_id_arm, pinocchio::LOCAL, J_right_arm);
    pinocchio::computeFrameJacobian(model, *data, q, right_frame_id_hand, pinocchio::LOCAL, J_right_hand);

    auto make_force = [](const Wrench6 &w) -> pinocchio::Force
    {
      pinocchio::Force f = pinocchio::Force::Zero();
      f.linear() << w.fx, w.fy, w.fz;
      f.angular() << w.mx, w.my, w.mz;
      return f;
    };

    pinocchio::Force f_left_arm = make_force(left_arm);
    pinocchio::Force f_left_hand = make_force(left_hand);
    pinocchio::Force f_right_arm = make_force(right_arm);
    pinocchio::Force f_right_hand = make_force(right_hand);

    Eigen::VectorXd tau_ext =
        J_left_arm.transpose() * f_left_arm.toVector() +
        J_left_hand.transpose() * f_left_hand.toVector() +
        J_right_arm.transpose() * f_right_arm.toVector() +
        J_right_hand.transpose() * f_right_hand.toVector();

    // ===================== 稳定阻尼项 =====================
    //
    // 原来的 -0.4 阻尼通过双重负号形成 +0.4*dq，实际属于运动助力。
    // 该运动助力现在已经迁移到统一的 viscous friction compensation 中。
    // 这里仅保留真正与速度反向的稳定阻尼，初始设为 0，以保持原有净效果。
    // 若实机出现振荡，可逐关节小幅增加为正数，例如 0.05、0.10。
    //
    Eigen::VectorXd stabilizing_damping = Eigen::VectorXd::Zero(model.nv);

    const std::array<double, 7> stabilizing_damping_value = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for (std::size_t i = 0; i < 7; ++i)
    {
      stabilizing_damping(left_v_id[i]) = stabilizing_damping_value[i];
      stabilizing_damping(right_v_id[i]) = stabilizing_damping_value[i];
    }

    Eigen::VectorXd tau_stabilizing_damping =
        -(stabilizing_damping.asDiagonal() * v);

    // ===================== 最终关节扭矩 =====================
    //
    // 此时 g 已包含：逐关节重力修正 + 逐关节摩擦补偿。
    // tau_ext 为四个六维力传感器映射得到的交互力矩。
    //
    Eigen::VectorXd tau =
        g + tau_ext + tau_stabilizing_damping;

    const std::array<double, 7> torque_limit = {
        30.0, 30.0, 30.0, 30.0, 18.0, 18.0, 18.0};

    auto write_torque = [&](std::size_t ctrl_id, int v_id, double sign, double limit)
    {
      output.use_torque[ctrl_id] = true;
      output.target_torque[ctrl_id] = clamp_abs(sign * tau(v_id), limit);
    };

    // ===================== 输出：左臂扭矩 =====================
    for (std::size_t i = 0; i < 7; ++i)
    {
      write_torque(left_ctrl_id[i], left_v_id[i], 1.0, torque_limit[i]);
    }

    // ===================== 输出：右臂扭矩 =====================
    //
    // 这里保留你原来双臂零力里对右臂力矩取负的处理。
    // 如果改成整体 URDF 后右臂方向已经完全统一，实机测试时可把 -1.0 改为 1.0。
    //
    for (std::size_t i = 0; i < 7; ++i)
    {
      write_torque(right_ctrl_id[i], right_v_id[i], -1.0, torque_limit[i]);
    }

    // ===================== 固定右臂末端 joint18~joint20 =====================
    output.use_position[IDX_R_J18] = true;
    output.target_position[IDX_R_J18] = 0.0;
    output.target_velocity[IDX_R_J18] = pulsePerMsToJointSpeedDegPerSecMagnitude(8, 1500.0);
    output.target_acc[IDX_R_J18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(8, 5.0);
    output.target_dec[IDX_R_J18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(8, 0.25);
    output.target_smooth_time[IDX_R_J18] = 25;

    output.use_position[IDX_R_J19] = true;
    output.target_position[IDX_R_J19] = 0.0;
    output.target_velocity[IDX_R_J19] = pulsePerMsToJointSpeedDegPerSecMagnitude(9, 1500.0);
    output.target_acc[IDX_R_J19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(9, 5.0);
    output.target_dec[IDX_R_J19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(9, 0.25);
    output.target_smooth_time[IDX_R_J19] = 25;

    output.use_position[IDX_R_J20] = true;
    output.target_position[IDX_R_J20] = 0.0;
    output.target_velocity[IDX_R_J20] = pulsePerMsToJointSpeedDegPerSecMagnitude(10, 1500.0);
    output.target_acc[IDX_R_J20] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(10, 5.0);
    output.target_dec[IDX_R_J20] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(10, 0.25);
    output.target_smooth_time[IDX_R_J20] = 25;

    // ===================== 固定左臂末端 joint8~joint10 =====================
    output.use_position[IDX_L_J8] = true;
    output.target_position[IDX_L_J8] = 0.0;
    output.target_velocity[IDX_L_J8] = pulsePerMsToJointSpeedDegPerSecMagnitude(18, 1500.0);
    output.target_acc[IDX_L_J8] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 5.0);
    output.target_dec[IDX_L_J8] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 0.25);
    output.target_smooth_time[IDX_L_J8] = 25;

    output.use_position[IDX_L_J9] = true;
    output.target_position[IDX_L_J9] = 0.0;
    output.target_velocity[IDX_L_J9] = pulsePerMsToJointSpeedDegPerSecMagnitude(19, 1500.0);
    output.target_acc[IDX_L_J9] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 5.0);
    output.target_dec[IDX_L_J9] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 0.25);
    output.target_smooth_time[IDX_L_J9] = 25;

    output.use_position[IDX_L_J10] = true;
    output.target_position[IDX_L_J10] = 0.0;
    output.target_velocity[IDX_L_J10] = pulsePerMsToJointSpeedDegPerSecMagnitude(20, 1500.0);
    output.target_acc[IDX_L_J10] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 5.0);
    output.target_dec[IDX_L_J10] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 0.25);
    output.target_smooth_time[IDX_L_J10] = 25;

    // ===================== 输出有效 =====================
    output.valid = true;
  }

  // ===================== 左臂预设位姿 =====================
  //
  // 当前实现：
  // 1. 只设置左臂相关控制层索引
  // 2. 左臂控制层索引范围为 10~19
  // 3. 目标位置单位是 deg
  // 4. 目标速度单位是 deg/s
  // 5. 目标加减速度单位是 deg/s^2
  // 注意：
  // 这里调用 pulsePerMsToJointSpeedDegPerSecMagnitude() 等辅助函数，
  // 是为了把旧代码里按 pulse/ms、pulse/ms^2 写的经验参数，
  // 转换成算法层统一使用的物理量单位。
  //
  void runLeftPresetPosition(const MotorStateCache &state, ControlOutputCache &output)
  {
    (void)state;

    output = ControlOutputCache{};
    output.valid = true;

    // ===================== 左臂 物理轴11 -> 控制层索引10 =====================
    output.use_position[10] = true;
    output.target_position[10] = 0.0;
    output.target_velocity[10] = pulsePerMsToJointSpeedDegPerSecMagnitude(11, 400.0);
    output.target_acc[10] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(11, 0.5);
    output.target_dec[10] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(11, 0.25);
    output.target_smooth_time[10] = 25;

    // ===================== 左臂 物理轴12 -> 控制层索引11 =====================
    output.use_position[11] = true;
    output.target_position[11] = 0.0;
    output.target_velocity[11] = pulsePerMsToJointSpeedDegPerSecMagnitude(12, 500.0);
    output.target_acc[11] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(12, 0.5);
    output.target_dec[11] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(12, 0.25);
    output.target_smooth_time[11] = 25;

    // ===================== 左臂 物理轴13 -> 控制层索引12 =====================
    output.use_position[12] = true;
    output.target_position[12] = 0.0;
    output.target_velocity[12] = pulsePerMsToJointSpeedDegPerSecMagnitude(13, 500.0);
    output.target_acc[12] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(13, 0.5);
    output.target_dec[12] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(13, 0.25);
    output.target_smooth_time[12] = 25;

    // ===================== 左臂 物理轴14 -> 控制层索引13 =====================
    output.use_position[13] = true;
    output.target_position[13] = 0.0;
    output.target_velocity[13] = pulsePerMsToJointSpeedDegPerSecMagnitude(14, 1500.0);
    output.target_acc[13] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(14, 5.0);
    output.target_dec[13] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(14, 5.0);
    output.target_smooth_time[13] = 25;

    // ===================== 左臂 物理轴15 -> 控制层索引14 =====================
    output.use_position[14] = true;
    output.target_position[14] = 0.0;
    output.target_velocity[14] = pulsePerMsToJointSpeedDegPerSecMagnitude(15, 1500.0);
    output.target_acc[14] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(15, 5.0);
    output.target_dec[14] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(15, 5.0);
    output.target_smooth_time[14] = 25;

    // ===================== 左臂 物理轴16 -> 控制层索引15 =====================
    output.use_position[15] = true;
    output.target_position[15] = 0.0;
    output.target_velocity[15] = pulsePerMsToJointSpeedDegPerSecMagnitude(16, 1500.0);
    output.target_acc[15] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(16, 5.0);
    output.target_dec[15] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(16, 5.0);
    output.target_smooth_time[15] = 25;

    // ===================== 左臂 物理轴17 -> 控制层索引16 =====================
    output.use_position[16] = true;
    output.target_position[16] = 45.0;
    output.target_velocity[16] = pulsePerMsToJointSpeedDegPerSecMagnitude(17, 1500.0);
    output.target_acc[16] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(17, 5.0);
    output.target_dec[16] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(17, 0.25);
    output.target_smooth_time[16] = 25;

    // ===================== 左臂 物理轴18 -> 控制层索引17 =====================
    output.use_position[17] = true;
    output.target_position[17] = 0.0;
    output.target_velocity[17] = pulsePerMsToJointSpeedDegPerSecMagnitude(18, 1500.0);
    output.target_acc[17] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 5.0);
    output.target_dec[17] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(18, 0.25);
    output.target_smooth_time[17] = 25;

    // ===================== 左臂 物理轴19 -> 控制层索引18 =====================
    output.use_position[18] = true;
    output.target_position[18] = 0.0;
    output.target_velocity[18] = pulsePerMsToJointSpeedDegPerSecMagnitude(19, 1500.0);
    output.target_acc[18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 5.0);
    output.target_dec[18] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(19, 0.25);
    output.target_smooth_time[18] = 25;

    // ===================== 左臂 物理轴20 -> 控制层索引19 =====================
    output.use_position[19] = true;
    output.target_position[19] = 0.0;
    output.target_velocity[19] = pulsePerMsToJointSpeedDegPerSecMagnitude(20, 1500.0);
    output.target_acc[19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 5.0);
    output.target_dec[19] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(20, 0.25);
    output.target_smooth_time[19] = 25;
  }

  // ===================== 右臂预设位姿 =====================
  //
  // 当前实现：
  // 1. 只设置右臂相关控制层索引
  // 2. 右臂控制层索引范围为 0~9
  // 3. 目标位置单位是 deg
  // 4. 目标速度单位是 deg/s
  // 5. 目标加减速度单位是 deg/s^2
  //
  void runRightPresetPosition(const MotorStateCache &state, ControlOutputCache &output)
  {
    (void)state;

    output = ControlOutputCache{};
    output.valid = true;

    // ===================== 右臂 物理轴1 -> 控制层索引0 =====================
    output.use_position[0] = true;
    output.target_position[0] = 0.0;
    output.target_velocity[0] = pulsePerMsToJointSpeedDegPerSecMagnitude(1, 200.0);
    output.target_acc[0] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(1, 0.5);
    output.target_dec[0] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(1, 0.25);
    output.target_smooth_time[0] = 25;

    // ===================== 右臂 物理轴2 -> 控制层索引1 =====================
    output.use_position[1] = true;
    output.target_position[1] = 0.0;
    output.target_velocity[1] = pulsePerMsToJointSpeedDegPerSecMagnitude(2, 500.0);
    output.target_acc[1] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(2, 0.5);
    output.target_dec[1] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(2, 0.25);
    output.target_smooth_time[1] = 25;

    // ===================== 右臂 物理轴3 -> 控制层索引2 =====================
    output.use_position[2] = true;
    output.target_position[2] = 0.0;
    output.target_velocity[2] = pulsePerMsToJointSpeedDegPerSecMagnitude(3, 500.0);
    output.target_acc[2] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(3, 0.5);
    output.target_dec[2] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(3, 0.25);
    output.target_smooth_time[2] = 25;

    // ===================== 右臂 物理轴4 -> 控制层索引3 =====================
    output.use_position[3] = true;
    output.target_position[3] = 0.0;
    output.target_velocity[3] = pulsePerMsToJointSpeedDegPerSecMagnitude(4, 800.0);
    output.target_acc[3] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(4, 0.5);
    output.target_dec[3] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(4, 0.25);
    output.target_smooth_time[3] = 25;

    // ===================== 右臂 物理轴5 -> 控制层索引4 =====================
    output.use_position[4] = true;
    output.target_position[4] = 0.0;
    output.target_velocity[4] = pulsePerMsToJointSpeedDegPerSecMagnitude(5, 600.0);
    output.target_acc[4] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(5, 5.0);
    output.target_dec[4] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(5, 0.25);
    output.target_smooth_time[4] = 25;

    // ===================== 右臂 物理轴6 -> 控制层索引5 =====================
    output.use_position[5] = true;
    output.target_position[5] = 0.0;
    output.target_velocity[5] = pulsePerMsToJointSpeedDegPerSecMagnitude(6, 600.0);
    output.target_acc[5] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(6, 5.0);
    output.target_dec[5] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(6, 0.25);
    output.target_smooth_time[5] = 25;

    // ===================== 右臂 物理轴7 -> 控制层索引6 =====================
    output.use_position[6] = true;
    output.target_position[6] = 45.0;
    output.target_velocity[6] = pulsePerMsToJointSpeedDegPerSecMagnitude(7, 3600.0);
    output.target_acc[6] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(7, 5.0);
    output.target_dec[6] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(7, 0.25);
    output.target_smooth_time[6] = 25;

    // 控制层索引7 当前未设置，保持默认值

    // ===================== 右臂 物理轴9 -> 控制层索引8 =====================
    output.use_position[8] = true;
    output.target_position[8] = 0.0;
    output.target_velocity[8] = pulsePerMsToJointSpeedDegPerSecMagnitude(9, 9000.0);
    output.target_acc[8] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(9, 5.0);
    output.target_dec[8] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(9, 0.25);
    output.target_smooth_time[8] = 25;

    // ===================== 右臂 物理轴10 -> 控制层索引9 =====================
    output.use_position[9] = true;
    output.target_position[9] = 0.0;
    output.target_velocity[9] = pulsePerMsToJointSpeedDegPerSecMagnitude(10, 3000.0);
    output.target_acc[9] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(10, 5.0);
    output.target_dec[9] = pulsePerMs2ToJointAccelDegPerSec2Magnitude(10, 0.25);
    output.target_smooth_time[9] = 25;
  }

  // ===================== SSVEP 脑电动作状态机 =====================
  void SsvepControl::reset(bool debug_mode)
  {
    status_ = SsvepStatus{};
    status_.phase = SsvepPhase::Ready;
    status_.ready_for_command = true;
    status_.debug_mode = debug_mode;
    status_.detail = "脑电模式已就绪，保持双臂零力等待";
    travel_deg_ = debug_mode ? SSVEP_DEBUG_TRAVEL_DEG : SSVEP_HARDWARE_TRAVEL_DEG;
    phase_time_s_ = 0.0;
    stable_cycles_ = 0;
    neutral_received_ = true;
    cooldown_active_ = false;
  }

  bool SsvepControl::requestTarget(
      std::uint8_t target,
      const MotorStateCache &state,
      std::string &reason)
  {
    if (target == 0)
    {
      neutral_received_ = true;
      status_.ready_for_command =
          status_.phase == SsvepPhase::Ready && !cooldown_active_;
      if (status_.ready_for_command)
      {
        status_.detail = "收到0号结果，已允许下一次脑电动作";
      }
      else if (status_.phase == SsvepPhase::Ready && cooldown_active_)
      {
        status_.detail = "已收到0号结果，等待触发冷却结束";
      }
      reason = "收到0号结果，已允许下一次触发";
      return false;
    }

    if (target >= SSVEP_TARGET_AXIS.size() || SSVEP_TARGET_AXIS[target] < 0)
    {
      reason = "目标编号超出范围";
      return false;
    }
    if (status_.phase != SsvepPhase::Ready)
    {
      reason = "动作执行中，普通指令已丢弃";
      return false;
    }
    if (!neutral_received_)
    {
      reason = "等待0号结果重新解锁";
      return false;
    }

    const int axis = SSVEP_TARGET_AXIS[target];
    const double goal = state.position[axis] + SSVEP_TARGET_DIRECTION[target] * travel_deg_;
    if (!std::isfinite(goal) || goal < SSVEP_TARGET_MIN_DEG[target] || goal > SSVEP_TARGET_MAX_DEG[target])
    {
      reason = "目标位置超过当前配置的安全范围";
      return false;
    }

    status_.target = target;
    status_.q0_deg = state.position;
    status_.target_deg = state.position;
    status_.target_deg[axis] = goal;
    status_.actual_deg = state.position;
    status_.phase = SsvepPhase::Switching;
    status_.ready_for_command = false;
    status_.detail = "已捕获实际q0，准备从零力切换到位置控制";
    phase_time_s_ = 0.0;
    stable_cycles_ = 0;
    neutral_received_ = false;
    reason = "动作已锁定";
    return true;
  }

  void SsvepControl::emergencyStop(const std::string &reason)
  {
    setFault(reason.empty() ? "安全停止" : reason);
  }

  double SsvepControl::smoothStep(double value)
  {
    const double x = std::clamp(value, 0.0, 1.0);
    return x * x * (3.0 - 2.0 * x);
  }

  void SsvepControl::setPositionOutput(double fraction, ControlOutputCache &output) const
  {
    output = ControlOutputCache{};
    const double s = smoothStep(fraction);
    for (std::size_t i = 0; i < AXIS_NUM; ++i)
    {
      const bool controlled = (i <= 6) || (i >= 10 && i <= 16);
      if (!controlled)
      {
        continue;
      }
      output.use_position[i] = true;
      output.target_position[i] = status_.q0_deg[i] +
          (status_.target_deg[i] - status_.q0_deg[i]) * s;
      output.target_velocity[i] = SSVEP_COMMAND_VELOCITY_DEG_S;
      output.target_acc[i] = SSVEP_COMMAND_ACCEL_DEG_S2;
      output.target_dec[i] = SSVEP_COMMAND_ACCEL_DEG_S2;
      output.target_smooth_time[i] = 20;
    }
    output.valid = true;
  }

  bool SsvepControl::targetReached(
      const MotorStateCache &state,
      const std::array<double, AXIS_NUM> &target) const
  {
    if (status_.target == 0 || status_.target >= SSVEP_TARGET_AXIS.size())
    {
      return false;
    }
    const int axis = SSVEP_TARGET_AXIS[status_.target];
    return std::abs(state.position[axis] - target[axis]) <= SSVEP_POSITION_TOLERANCE_DEG &&
           std::abs(state.velocity[axis]) <= SSVEP_STOP_VELOCITY_DEG_S;
  }

  void SsvepControl::setFault(const std::string &reason)
  {
    status_.phase = SsvepPhase::Fault;
    status_.target = 0;
    status_.ready_for_command = false;
    status_.detail = reason;
  }

  void SsvepControl::run(
      const MotorStateCache &state,
      const SensorStateCache &sensor_state,
      double dt_s,
      ControlOutputCache &output)
  {
    status_.actual_deg = state.position;
    const double dt = std::clamp(dt_s, 0.0001, 0.1);
    phase_time_s_ += dt;

    switch (status_.phase)
    {
    case SsvepPhase::ZeroForce:
    case SsvepPhase::Ready:
      runBilateralZeroForceMode(state, sensor_state, output);
      status_.phase = SsvepPhase::Ready;
      if (cooldown_active_ &&
          phase_time_s_ * 1000.0 >= static_cast<double>(SSVEP_COOLDOWN_MS))
      {
        cooldown_active_ = false;
        if (neutral_received_)
        {
          status_.detail = "冷却结束且已收到0号结果，允许下一次脑电动作";
        }
      }
      status_.ready_for_command = neutral_received_ && !cooldown_active_;
      break;

    case SsvepPhase::Switching:
      // 第一帧仅保持 q0。执行层会核对真实驱动模式并同步规划位置。
      setPositionOutput(0.0, output);
      status_.phase = SsvepPhase::MovingOut;
      status_.detail = "位置模式接管，执行去程";
      phase_time_s_ = 0.0;
      break;

    case SsvepPhase::MovingOut:
      setPositionOutput(phase_time_s_ / SSVEP_MOVE_SECONDS, output);
      if (phase_time_s_ >= SSVEP_MOVE_SECONDS && targetReached(state, status_.target_deg))
      {
        status_.phase = SsvepPhase::MovingBack;
        status_.detail = "去程到位，执行返程";
        phase_time_s_ = 0.0;
      }
      else if (phase_time_s_ > SSVEP_MOVE_SECONDS + SSVEP_SETTLE_TIMEOUT_SECONDS)
      {
        setFault("去程超时，未达到位置/速度阈值");
        output = ControlOutputCache{};
      }
      break;

    case SsvepPhase::MovingBack:
      setPositionOutput(1.0 - phase_time_s_ / SSVEP_MOVE_SECONDS, output);
      if (phase_time_s_ >= SSVEP_MOVE_SECONDS && targetReached(state, status_.q0_deg))
      {
        status_.phase = SsvepPhase::Settling;
        status_.detail = "返程到位，等待稳定";
        phase_time_s_ = 0.0;
        stable_cycles_ = 0;
      }
      else if (phase_time_s_ > SSVEP_MOVE_SECONDS + SSVEP_SETTLE_TIMEOUT_SECONDS)
      {
        setFault("返程超时，未回到q0附近");
        output = ControlOutputCache{};
      }
      break;

    case SsvepPhase::Settling:
      setPositionOutput(0.0, output);
      if (targetReached(state, status_.q0_deg))
      {
        ++stable_cycles_;
        if (stable_cycles_ >= 5)
        {
          status_.phase = SsvepPhase::RestoringZeroForce;
          status_.detail = "位置稳定，恢复零力";
          phase_time_s_ = 0.0;
        }
      }
      else
      {
        stable_cycles_ = 0;
        if (phase_time_s_ > SSVEP_SETTLE_TIMEOUT_SECONDS)
        {
          setFault("稳定等待超时");
          output = ControlOutputCache{};
        }
      }
      break;

    case SsvepPhase::RestoringZeroForce:
      runBilateralZeroForceMode(state, sensor_state, output);
      status_.phase = SsvepPhase::Ready;
      status_.target = 0;
      status_.ready_for_command = false;
      status_.detail = "往返完成并恢复零力，等待0号结果重新解锁";
      phase_time_s_ = 0.0;
      cooldown_active_ = true;
      break;

    case SsvepPhase::Fault:
      output = ControlOutputCache{};
      output.valid = false;
      break;
    }
  }

} // namespace upperlimb_robot
