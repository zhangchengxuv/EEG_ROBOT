# RobotState.msg
# 定义机器人与GUI交互的数据

float64[] position
float64[] velocity
float64[] torque
bool[] enabled

# 四个六维力传感器合并后的数组，长度固定为 24
# 顺序约定：
# [右手fx, 右手fy, 右手fz, 右手mx, 右手my, 右手mz,
#  右臂fx, 右臂fy, 右臂fz, 右臂mx, 右臂my, 右臂mz,
#  左手fx, 左手fy, 左手fz, 左手mx, 左手my, 左手mz,
#  左臂fx, 左臂fy, 左臂fz, 左臂mx, 左臂my, 左臂mz]
float64[] force_sensor