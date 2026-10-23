# ROS 2 控制工作区

控制、串口接收、SSVEP 协议解析、动作状态机和机器人执行均合并在
`upperlimb_robot` 包的一个 `robot_control_node` 中。串口使用 POSIX
`termios`，不依赖 Qt SerialPort。

保留的控制模式只有：空闲、左右臂初始位置、左/右/双臂零力和 SSVEP。
旧的主动、被动、镜像、虚拟弹簧及强化学习算法实现和功能包均已删除。

## 构建

```bash
source /opt/ros/humble/setup.bash
cd /home/zhangchenxu/Documents/00_Project/EEG_ROBOT/ros2
colcon build --packages-select upperlimb_robot
source install/setup.bash
```

## 无硬件调试

```bash
ros2 run upperlimb_robot robot_control_node --ros-args \
  -p hardware_enabled:=false
```

该参数会阻止节点初始化或调用 GTN/EtherCAT。GUI 的测试按钮仍会经过同一个
SSVEP 动作状态机，并由节点内的关节反馈模拟器完成往返动作。

## 实机与串口

```bash
ros2 run upperlimb_robot robot_control_node --ros-args \
  -p hardware_enabled:=true \
  -p ssvep.serial_device:=/dev/ttyUSB0
```

串口固定使用 115200、8N1、无流控，帧格式为
`RESULT,序号,EEG,目标编号,频率\r\n`。设备路径必须按现场实际设备设置。
所有帧（包括无效、重复、旧序号和动作忙碌）通过 `ssvep/result` 发布；
动作状态通过 `ssvep/action_status` 发布。GUI 只订阅这些 ROS 2 消息。

首次实机运行前必须核对机械限位、轴方向和急停；当前实机单次行程默认仅 1°，
该默认值仍不代表已完成实机安全验证。

## 自动化测试

```bash
source /opt/ros/humble/setup.bash
cd /home/zhangchenxu/Documents/00_Project/EEG_ROBOT/ros2
colcon test --packages-select upperlimb_robot
colcon test-result --verbose
```

测试覆盖串口协议合法/非法/重复/旧序号，四个目标的关节映射、动作期间互斥、
完整往返与 0 号重新解锁，以及不受动作锁限制的安全停止。
