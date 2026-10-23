# GUI -> 唯一 robot_control_node 的控制命令。
# command: 0=空闲，1=左预设位，2=右预设位，4=左零力，8=右零力，
#          9=双臂零力，19=SSVEP 脑电模式。
int32 command

# 仅在 SSVEP 模式中使用。true 时禁止访问硬件，以内部机器人模型验证完整状态机。
bool ssvep_debug

# 调试模式人工目标：0=无目标/重新解锁，1=左肩，2=右肩，3=左肘，4=右肘。
# 非调试模式下该字段被忽略。
uint8 ssvep_test_target

# 高优先级安全停止，不受动作互斥限制。
bool emergency_stop
