#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace upperlimb_robot
{

  // ===================== 系统常量定义 =====================

  // 总轴数
  // 控制层内部数组索引统一使用 0~19
  static constexpr std::size_t AXIS_NUM = 20;

  // 六维力传感器数量
  // 传感器数组索引统一使用 0~3
  static constexpr std::size_t FORCE_SENSOR_NUM = 4;

  // ===================== 统一重力补偿参数 =====================
  //
  // 所有使用 Pinocchio 重力力矩的控制算法都共用这里的参数。
  // 左右臂分别配置，并且每条臂的 7 个主动关节分别配置。
  //
  // 修正公式：
  //   tau_gravity[i] = gain[i] * tau_gravity_model[i] + bias_nm[i]
  //
  // 参数顺序：
  //   左臂：joint1  ~ joint7
  //   右臂：joint11 ~ joint17
  //
  // 注意：bias_nm 使用 Pinocchio 模型方向，右臂最终发送时的整体负号
  // 仍由各控制算法原有的驱动方向映射负责。
  struct GravityCompensationParameters
  {
    std::array<double, 7> gain{};
    std::array<double, 7> bias_nm{};
  };

  extern const GravityCompensationParameters LEFT_ARM_GRAVITY_COMPENSATION;
  extern const GravityCompensationParameters RIGHT_ARM_GRAVITY_COMPENSATION;

  // ===================== 统一关节摩擦补偿参数 =====================
  //
  // 所有扭矩控制算法共用这里的摩擦补偿参数。
  // 左右臂分别配置，并且每条臂的 7 个主动关节分别配置。
  //
  // 补偿公式：
  //   tau_friction[i]
  //       = coulomb_nm[i] * tanh(dq[i] / velocity_smooth_rad_s[i])
  //       + viscous_nm_per_rad_s[i] * dq[i]
  //
  // 参数含义：
  //   coulomb_nm              -> 低速近似恒定的库仑摩擦补偿，单位 Nm；
  //   viscous_nm_per_rad_s    -> 随速度增加的粘性摩擦补偿，单位 Nm/(rad/s)；
  //   velocity_smooth_rad_s   -> 零速度附近的方向平滑范围，单位 rad/s。
  //
  // tau_friction 与实际关节速度方向相同，用于抵消机构摩擦。
  // 右臂最终发送时的整体负号仍由各控制算法原有的驱动方向映射负责。
  struct FrictionCompensationParameters
  {
    std::array<double, 7> coulomb_nm{};
    std::array<double, 7> viscous_nm_per_rad_s{};
    std::array<double, 7> velocity_smooth_rad_s{};
  };

  extern const FrictionCompensationParameters LEFT_ARM_FRICTION_COMPENSATION;
  extern const FrictionCompensationParameters RIGHT_ARM_FRICTION_COMPENSATION;

  // ===================== 控制模式定义 =====================
  //
  // 说明：
  // 1. current_mode_ 表示“请求模式”
  // 2. applied_mode_ 表示“已经完成进入动作的模式”
  // 3. 真正的模式进入/退出动作建议在 onModeEnter()/onModeExit() 中执行
  //
  enum ControlMode : int
  {
    // 空闲模式
    // 默认不输出控制命令
    MODE_IDLE = 0,

    // 左臂预设位置模式
    MODE_LEFT_PRESET_POSITION = 1,

    // 右臂预设位置模式
    MODE_RIGHT_PRESET_POSITION = 2,

    // 左臂零力模式
    MODE_ZERO_FORCE = 4,

    // 右臂零力模式
    MODE_RIGHT_ZERO_FORCE = 8,

    // 双臂零力模式
    MODE_BILATERAL_ZERO_FORCE = 9,

    // SSVEP 脑电控制：零力等待 -> 小幅往返 -> 自动恢复零力
    MODE_SSVEP = 19,

  };

  // ===================== 电机状态缓存 =====================
  //
  // 对外统一使用真实物理量：
  // position : deg
  // velocity : deg/s
  // torque   : Nm
  //
  // 注意：
  // 1. 这里的下标是“控制层数组索引 0~19”
  // 2. 不一定等于 GTN 物理轴号 1~20
  // 3. 真正访问驱动时，应通过 axis_ids_[i] 做映射
  //
  struct MotorStateCache
  {
    // 数组索引 0~19
    // 关节位置，单位 deg
    std::array<double, AXIS_NUM> position{};

    // 数组索引 0~19
    // 关节速度，单位 deg/s
    std::array<double, AXIS_NUM> velocity{};

    // 数组索引 0~19
    // 关节扭矩，单位 Nm
    std::array<double, AXIS_NUM> torque{};

    // 数组索引 0~19
    // 轴是否使能
    std::array<bool, AXIS_NUM> enable{};
  };

  // ===================== 单个六维力传感器 =====================
  //
  // 力单位：N
  // 力矩单位：Nm
  //
  struct ForceSensorData
  {
    double fx{0.0};
    double fy{0.0};
    double fz{0.0};
    double mx{0.0};
    double my{0.0};
    double mz{0.0};
  };

  // ===================== 传感器索引定义 =====================
  //
  // sensor[0~3] / bias[0~3] 的索引约定
  //
  enum ForceSensorIndex : std::size_t
  {
    SENSOR_RIGHT_HAND = 0,
    SENSOR_RIGHT_ARM = 1,
    SENSOR_LEFT_HAND = 2,
    SENSOR_LEFT_ARM = 3,
  };

  // ===================== 传感器状态缓存 =====================
  //
  // sensor : 当前实时值
  // bias   : 已记录的零偏
  // valid  : 当前实时值是否有效
  //
  // 说明：
  // valid == true 表示本轮读取成功
  // valid == false 时，不应拿当前 sensor 直接记录 bias
  //
  struct SensorStateCache
  {
    // 数组索引 0~3
    // 当前实时传感器值
    std::array<ForceSensorData, FORCE_SENSOR_NUM> sensor{};

    // 数组索引 0~3
    // 零偏值
    std::array<ForceSensorData, FORCE_SENSOR_NUM> bias{};

    // 当前传感器缓存是否有效
    bool valid{false};
  };

  // ===================== 控制输出缓存 =====================
  //
  // 这是“算法层 -> 执行层”的统一输出接口。
  //
  // 约定：
  // 1. 数组索引统一为 0~19
  // 2. 算法层统一使用真实物理量
  // 3. target_torque 的单位是 Nm，不是 raw
  // 4. 正常写法为：output.target_torque[6] = 2.0;（2.0 Nm）
  // 5. 允许不同轴使用不同控制方式，例如左臂位置模式、右臂扭矩模式；
  //    但同一个轴不能同时把 use_position 和 use_torque 设为 true。
  //
  struct ControlOutputCache
  {
    // 数组索引 0~19
    // 目标位置，单位 deg
    std::array<double, AXIS_NUM> target_position{};

    // 数组索引 0~19
    // 目标速度，单位 deg/s
    std::array<double, AXIS_NUM> target_velocity{};

    // 数组索引 0~19
    // 目标扭矩，单位 Nm
    // 正常写法为：output.target_torque[6] = 2.0;（2.0 Nm）
    std::array<double, AXIS_NUM> target_torque{};

    // 数组索引 0~19
    // 目标加速度，单位 deg/s^2
    std::array<double, AXIS_NUM> target_acc{};

    // 数组索引 0~19
    // 目标减速度，单位 deg/s^2
    std::array<double, AXIS_NUM> target_dec{};

    // 数组索引 0~19
    // 平滑时间，单位由底层驱动接口定义
    std::array<short, AXIS_NUM> target_smooth_time{};

    // 数组索引 0~19
    // 是否对该轴启用位置控制
    std::array<bool, AXIS_NUM> use_position{};

    // 数组索引 0~19
    // 是否显式使用速度字段
    // 当前版本主要作为语义保留
    std::array<bool, AXIS_NUM> use_velocity{};

    // 数组索引 0~19
    // 是否对该轴启用扭矩控制
    std::array<bool, AXIS_NUM> use_torque{};

    // 输出是否有效
    // valid == false 时，执行层应跳过本轮控制输出
    bool valid{false};

  };

  // ===================== SSVEP 串口与运动参数 =====================
  // 串口路径由 ROS 参数 ssvep.serial_device 覆盖；空字符串表示不打开串口。
  inline constexpr const char *SSVEP_DEFAULT_SERIAL_DEVICE = "";
  inline constexpr int SSVEP_SERIAL_BAUD = 115200;
  inline constexpr std::size_t SSVEP_MAX_FRAME_BYTES = 256;
  inline constexpr double SSVEP_DEBUG_TRAVEL_DEG = 3.0;
  inline constexpr double SSVEP_HARDWARE_TRAVEL_DEG = 1.0;
  inline constexpr double SSVEP_MOVE_SECONDS = 1.5;
  inline constexpr double SSVEP_SETTLE_TIMEOUT_SECONDS = 2.0;
  inline constexpr double SSVEP_POSITION_TOLERANCE_DEG = 0.35;
  inline constexpr double SSVEP_STOP_VELOCITY_DEG_S = 1.0;
  inline constexpr double SSVEP_COMMAND_VELOCITY_DEG_S = 5.0;
  inline constexpr double SSVEP_COMMAND_ACCEL_DEG_S2 = 10.0;
  inline constexpr int SSVEP_COOLDOWN_MS = 1200;

  struct SsvepFrameResult
  {
    // 0=接受，1=格式错误，2=重复序号，3=旧序号，4=超长帧，5=串口异常，6=忙碌丢弃
    std::uint8_t status{1};
    std::string detail;
    std::uint64_t sequence{0};
    std::string source;
    std::uint8_t target{0};
    double frequency_hz{0.0};
  };

  // 解析单个不含 CRLF 的协议帧，并在校验通过后更新 last_sequence。
  SsvepFrameResult parseSsvepProtocolFrame(
      const std::string &raw,
      std::int64_t &last_sequence);

  // 目标到控制层索引的映射：左肩 joint3=12，右肩 joint13=2，
  // 左肘 joint6=15，右肘 joint16=5。物理轴号由 node 的 axis_ids_ 映射。
  inline constexpr std::array<int, 5> SSVEP_TARGET_AXIS = {-1, 12, 2, 15, 5};
  inline constexpr std::array<double, 5> SSVEP_TARGET_DIRECTION = {0.0, 1.0, 1.0, 1.0, 1.0};
  inline constexpr std::array<double, 5> SSVEP_TARGET_MIN_DEG = {0.0, -90.0, -90.0, -90.0, -90.0};
  inline constexpr std::array<double, 5> SSVEP_TARGET_MAX_DEG = {0.0, 90.0, 90.0, 90.0, 90.0};

  enum class SsvepPhase : std::uint8_t
  {
    ZeroForce = 0,
    Ready = 1,
    Switching = 2,
    MovingOut = 3,
    MovingBack = 4,
    Settling = 5,
    RestoringZeroForce = 6,
    Fault = 7
  };

  struct SsvepStatus
  {
    SsvepPhase phase{SsvepPhase::ZeroForce};
    std::uint8_t target{0};
    bool ready_for_command{false};
    bool debug_mode{true};
    std::string detail{"未进入脑电模式"};
    std::array<double, AXIS_NUM> q0_deg{};
    std::array<double, AXIS_NUM> target_deg{};
    std::array<double, AXIS_NUM> actual_deg{};
  };

  class SsvepControl
  {
  public:
    void reset(bool debug_mode);
    bool requestTarget(std::uint8_t target, const MotorStateCache &state, std::string &reason);
    void emergencyStop(const std::string &reason);
    void run(const MotorStateCache &state,
             const SensorStateCache &sensor_state,
             double dt_s,
             ControlOutputCache &output);
    const SsvepStatus &status() const { return status_; }

  private:
    void setPositionOutput(double fraction, ControlOutputCache &output) const;
    bool targetReached(const MotorStateCache &state, const std::array<double, AXIS_NUM> &target) const;
    void setFault(const std::string &reason);
    static double smoothStep(double value);

    SsvepStatus status_{};
    double phase_time_s_{0.0};
    double travel_deg_{SSVEP_DEBUG_TRAVEL_DEG};
    int stable_cycles_{0};
    bool neutral_received_{true};
    bool cooldown_active_{false};
  };

  // ===================== 单位换算接口 =====================
  //
  // 注意：
  // 这些换算函数传入的是“真实物理轴号 axis（1~20）”
  // 不是控制层数组索引 i（0~19）
  //
  double jointDegToPulse(int axis, double joint_deg);
  double pulseToJointDeg(int axis, double pulse);

  double jointSpeedDegPerSecToPulsePerMs(int axis, double joint_speed_deg_per_sec);
  double pulsePerMsToJointDegPerSec(int axis, double pulse_per_ms);

  double jointAccelDegPerSec2ToPulsePerMs2(int axis, double joint_acc_deg_per_sec2);
  double pulsePerMs2ToJointDegPerSec2(int axis, double pulse_per_ms2);

  // raw -> Nm
  // 用于“读取驱动反馈扭矩”
  double torqueRawToNm(int axis, double raw);

  // Nm -> raw
  // 用于“下发驱动扭矩命令”
  double torqueNmToRaw(int axis, double torque_nm);

  // ===================== 控制算法接口 =====================
  // 不需要需要传感器信息

  // 空闲模式
  void runIdle(const MotorStateCache &state, ControlOutputCache &output);
  // 预设位姿模式
  void runLeftPresetPosition(const MotorStateCache &state, ControlOutputCache &output);
  void runRightPresetPosition(const MotorStateCache &state, ControlOutputCache &output);

  // 需要传感器信息的算法

  // MotorStateCache 提供位置、速度、扭矩等电机状态信息
  // SensorStateCache        提供六维力传感器信息
  // ControlOutputCache      提供输出接口

  // 左边零力模式
  void runZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output);
  // 右边零力模式
  void runRightZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output);
  // 双臂零力模式
  void runBilateralZeroForceMode(const MotorStateCache &state, const SensorStateCache &sensor_state, ControlOutputCache &output);

} // namespace upperlimb_robot
