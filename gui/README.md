# 上肢外骨骼 SSVEP GUI 工作区

Qt Widgets 界面只通过 ROS 2 与控制节点通信，不打开串口，也不链接
`Qt5SerialPort`。

界面提供：左右臂初始位置、左/右/双臂零力、脑电控制、空闲、安全停止，
以及脑电模式下的实机/调试切换和四个调试目标按钮。串口连接状态、设备、
波特率、原始帧、解析结果、当前动作、动作阶段和是否允许接收下一指令均来自
ROS 2 订阅。主界面同时显示左右臂 14 个主动关节的位置、速度、力矩、使能状态，
以及右手、右臂、左手、左臂四组六维力传感器数据。

## 构建与启动

先构建并加载控制工作区，然后构建 GUI：

```bash
source /opt/ros/humble/setup.bash
source /home/zhangchenxu/Documents/00_Project/EEG_ROBOT/ros2/install/setup.bash
cd /home/zhangchenxu/Documents/00_Project/EEG_ROBOT/gui
colcon build --packages-select ssvep_gui
source install/setup.bash
ros2 run ssvep_gui ssvep_gui_node
```

无硬件联调时，先按 ROS 2 工作区说明以 `hardware_enabled:=false` 启动唯一的
`robot_control_node`，再启动 GUI，进入“脑电控制”并保持“调试”即可使用四个
目标按钮。切换到“实机”不会自动触发动作；串口 EEG 帧只在实机脑电模式中
进入动作状态机。一次往返结束后需先收到 0 号结果，并经过 1200 ms 冷却时间，
界面显示“允许下一动作”后才会接收新的非零目标。
