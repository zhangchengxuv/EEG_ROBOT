#include <QAbstractItemView>
#include <QApplication>
#include <QButtonGroup>
#include <QCloseEvent>
#include <QDateTime>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMutex>
#include <QMutexLocker>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSizePolicy>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>

#include <rclcpp/executors/single_threaded_executor.hpp>
#include <rclcpp/rclcpp.hpp>
#include <upperlimb_robot/msg/control_command.hpp>
#include <upperlimb_robot/msg/robot_state.hpp>
#include <upperlimb_robot/msg/ssvep_action_status.hpp>
#include <upperlimb_robot/msg/ssvep_result.hpp>
#include <upperlimb_robot/msg/system_state.hpp>

#include <array>
#include <cstdint>
#include <thread>
#include <vector>

namespace {

constexpr int kIdle = 0;
constexpr int kLeftPreset = 1;
constexpr int kRightPreset = 2;
constexpr int kLeftZeroForce = 4;
constexpr int kRightZeroForce = 8;
constexpr int kBilateralZeroForce = 9;
constexpr int kSsvep = 19;

constexpr const char *kStyle = R"QSS(
QWidget {
  color: #dcecff;
  font-family: "Noto Sans CJK SC", "Microsoft YaHei", sans-serif;
  font-size: 13px;
}
QFrame#rootFrame {
  background: #0b1117;
  border: 1px solid #3a3a3a;
  border-radius: 22px;
}
QFrame#titleBar {
  background: #353535;
  border-top-left-radius: 21px;
  border-top-right-radius: 21px;
}
QLabel#windowTitle {
  color: #f7f7f7;
  font-size: 28px;
  font-weight: 400;
  letter-spacing: 1px;
}
QPushButton#minButton, QPushButton#maxButton, QPushButton#closeButton {
  border: none;
  border-radius: 13px;
  padding: 0;
  min-width: 26px;
  max-width: 26px;
  min-height: 26px;
  max-height: 26px;
}
QPushButton#minButton { background: #f6ad17; }
QPushButton#maxButton { background: #52c940; }
QPushButton#closeButton { background: #ef514b; }
QPushButton#minButton:hover { background: #ffc44c; }
QPushButton#maxButton:hover { background: #70dc5d; }
QPushButton#closeButton:hover { background: #ff706a; }
QGroupBox {
  background: #111820;
  border: 1px solid #2d3b4a;
  border-radius: 8px;
  margin-top: 11px;
  padding-top: 10px;
  font-weight: 600;
}
QGroupBox::title {
  subcontrol-origin: margin;
  subcontrol-position: top left;
  left: 10px;
  padding: 0 5px;
  color: #77bdf5;
}
QLabel[role="caption"] {
  color: #6f91ad;
  font-size: 12px;
  font-weight: 600;
}
QLabel[role="statusText"] {
  color: #dcecff;
  font-weight: 600;
}
QLabel[role="sectionTitle"] {
  color: #77bdf5;
  font-weight: 700;
}
QLabel[role="value"] {
  background: #0c131a;
  border-radius: 2px;
  color: #dcecff;
  padding: 3px 5px;
}
QLabel[role="forceValue"] {
  background: #0c131a;
  border-radius: 2px;
  color: #dcecff;
  font-size: 11px;
  padding: 0 4px;
}
QLabel[role="muted"] { color: #7d9bb6; }
QPushButton {
  background: #1c2733;
  border: 1px solid #35485a;
  border-radius: 6px;
  color: #e4f0ff;
  font-weight: 600;
  min-height: 34px;
  padding: 2px 10px;
}
QPushButton:hover { background: #243649; border-color: #4f789b; }
QPushButton:pressed { background: #14212d; }
QPushButton:checked { background: #1689c2; border-color: #38ace7; color: white; }
QPushButton:disabled { color: #546678; background: #141b23; border-color: #26323d; }
QPushButton[role="brain"] { background: #28243d; border-color: #474166; }
QPushButton[role="brain"]:hover { background: #343051; }
QPushButton[role="brain"]:checked { background: #1689c2; border-color: #38ace7; }
QPushButton[role="danger"] { background: #8e3030; border-color: #c44b4b; color: white; }
QPushButton[role="danger"]:hover { background: #b83d3d; }
QPushButton[role="modeDisplay"] {
  background: #1689c2;
  border-color: #35a9df;
  color: white;
}
QFrame[panel="sensor"], QFrame[panel="tile"] {
  background: #0d141b;
  border: 1px solid #1d2b38;
  border-radius: 5px;
}
QTableWidget {
  background: #111820;
  alternate-background-color: #151e27;
  border: 1px solid #2d3b4a;
  border-radius: 6px;
  gridline-color: #293746;
  color: #dcecff;
  selection-background-color: #1689c2;
}
QTableWidget::item { padding: 4px; }
QHeaderView::section {
  background: #1a2530;
  color: #9fcdf2;
  border: none;
  border-right: 1px solid #31404f;
  border-bottom: 1px solid #31404f;
  padding: 6px 3px;
  font-weight: 700;
}
QPlainTextEdit {
  background: #0c131a;
  border: 1px solid #2d3b4a;
  border-radius: 5px;
  color: #dcecff;
  selection-background-color: #1689c2;
  padding: 6px;
}
QScrollBar:vertical {
  background: #111820;
  width: 9px;
  margin: 0;
}
QScrollBar::handle:vertical { background: #405267; border-radius: 4px; min-height: 24px; }
QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }
)QSS";

class TitleBar final : public QFrame
{
public:
  explicit TitleBar(QWidget *parent = nullptr) : QFrame(parent)
  {
    setObjectName(QStringLiteral("titleBar"));
    setFixedHeight(64);
  }

protected:
  void mousePressEvent(QMouseEvent *event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      drag_offset_ = event->globalPos() - window()->frameGeometry().topLeft();
      dragging_ = true;
    }
    QFrame::mousePressEvent(event);
  }

  void mouseMoveEvent(QMouseEvent *event) override
  {
    if (dragging_ && (event->buttons() & Qt::LeftButton) && !window()->isMaximized())
    {
      window()->move(event->globalPos() - drag_offset_);
    }
    QFrame::mouseMoveEvent(event);
  }

  void mouseReleaseEvent(QMouseEvent *event) override
  {
    dragging_ = false;
    QFrame::mouseReleaseEvent(event);
  }

  void mouseDoubleClickEvent(QMouseEvent *event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      window()->isMaximized() ? window()->showNormal() : window()->showMaximized();
    }
    QFrame::mouseDoubleClickEvent(event);
  }

private:
  QPoint drag_offset_;
  bool dragging_{false};
};

}  // namespace

class SsvepGui final : public QMainWindow
{
  Q_OBJECT

public:
  SsvepGui()
  {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1180, 900);
    resize(1380, 1000);

    node_ = rclcpp::Node::make_shared("ssvep_gui");
    command_pub_ = node_->create_publisher<upperlimb_robot::msg::ControlCommand>("control_command", 20);
    system_sub_ = node_->create_subscription<upperlimb_robot::msg::SystemState>(
      "system_state", 10,
      [this](const upperlimb_robot::msg::SystemState::SharedPtr msg) {
        QMutexLocker lock(&mutex_);
        system_ = *msg;
        system_pending_ = true;
      });
    robot_sub_ = node_->create_subscription<upperlimb_robot::msg::RobotState>(
      "robot_state", 10,
      [this](const upperlimb_robot::msg::RobotState::SharedPtr msg) {
        QMutexLocker lock(&mutex_);
        robot_ = *msg;
        robot_pending_ = true;
      });
    result_sub_ = node_->create_subscription<upperlimb_robot::msg::SsvepResult>(
      "ssvep/result", rclcpp::QoS(50).reliable().transient_local(),
      [this](const upperlimb_robot::msg::SsvepResult::SharedPtr msg) {
        QMutexLocker lock(&mutex_);
        result_ = *msg;
        result_pending_ = true;
      });
    action_sub_ = node_->create_subscription<upperlimb_robot::msg::SsvepActionStatus>(
      "ssvep/action_status", 20,
      [this](const upperlimb_robot::msg::SsvepActionStatus::SharedPtr msg) {
        QMutexLocker lock(&mutex_);
        action_ = *msg;
        action_pending_ = true;
      });

    buildInterface();
    setStyleSheet(QString::fromUtf8(kStyle));

    executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor_->add_node(node_);
    spin_thread_ = std::thread([this] { executor_->spin(); });

    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SsvepGui::refresh);
    timer->start(100);
    appendLog(QStringLiteral("GUI 启动完成，等待 robot_control_node"));
  }

  ~SsvepGui() override
  {
    executor_->cancel();
    executor_->remove_node(node_);
    if (spin_thread_.joinable())
    {
      spin_thread_.join();
    }
  }

protected:
  void closeEvent(QCloseEvent *event) override
  {
    if (rclcpp::ok())
    {
      publishCommand(kSsvep, debug_selected_, 0, true);
    }
    QMainWindow::closeEvent(event);
  }

private:
  void buildInterface()
  {
    auto *host = new QWidget(this);
    host->setObjectName(QStringLiteral("windowHost"));
    host->setStyleSheet(QStringLiteral("QWidget#windowHost { background: transparent; }"));
    auto *host_layout = new QVBoxLayout(host);
    host_layout->setContentsMargins(10, 10, 10, 10);
    host_layout->setSpacing(0);

    auto *root_frame = new QFrame(host);
    root_frame->setObjectName(QStringLiteral("rootFrame"));
    auto *root = new QVBoxLayout(root_frame);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);
    root->addWidget(buildTitleBar());

    auto *content = new QWidget(root_frame);
    auto *content_layout = new QVBoxLayout(content);
    content_layout->setContentsMargins(9, 8, 9, 9);
    content_layout->setSpacing(7);
    content_layout->addWidget(buildSystemStatus());

    auto *main_row = new QHBoxLayout;
    main_row->setSpacing(9);
    main_row->addWidget(buildControlPanel());
    main_row->addWidget(buildSsvepPanel());

    auto *right_column = new QVBoxLayout;
    right_column->setSpacing(7);
    auto *joint_panel = buildJointPanel();
    auto *force_panel = buildForcePanel();
    auto *action_panel = buildActionPanel();
    auto *serial_panel = buildSerialPanel();
    auto *log_panel = buildLogPanel();
    joint_panel->setMinimumHeight(255);
    force_panel->setMinimumHeight(190);
    action_panel->setMinimumHeight(130);
    serial_panel->setMinimumHeight(130);
    log_panel->setMinimumHeight(90);
    right_column->addWidget(joint_panel);
    right_column->addWidget(force_panel);
    right_column->addWidget(action_panel);
    right_column->addWidget(serial_panel);
    right_column->addWidget(log_panel, 1);
    main_row->addLayout(right_column, 1);
    content_layout->addLayout(main_row, 1);
    root->addWidget(content, 1);
    host_layout->addWidget(root_frame);
    setCentralWidget(host);
  }

  QWidget *buildTitleBar()
  {
    auto *bar = new TitleBar(this);
    auto *layout = new QHBoxLayout(bar);
    layout->setContentsMargins(22, 0, 22, 0);
    layout->addStretch();

    auto *title = new QLabel(QStringLiteral("UpperLimb GUI"), bar);
    title->setObjectName(QStringLiteral("windowTitle"));
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    layout->addStretch();

    auto *buttons = new QHBoxLayout;
    buttons->setSpacing(16);
    auto *minimize = new QPushButton(bar);
    auto *maximize = new QPushButton(bar);
    auto *close = new QPushButton(bar);
    minimize->setObjectName(QStringLiteral("minButton"));
    maximize->setObjectName(QStringLiteral("maxButton"));
    close->setObjectName(QStringLiteral("closeButton"));
    minimize->setToolTip(QStringLiteral("最小化"));
    maximize->setToolTip(QStringLiteral("最大化/还原"));
    close->setToolTip(QStringLiteral("关闭并安全停止"));
    connect(minimize, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(maximize, &QPushButton::clicked, this, [this] {
      isMaximized() ? showNormal() : showMaximized();
    });
    connect(close, &QPushButton::clicked, this, &QWidget::close);
    buttons->addWidget(minimize);
    buttons->addWidget(maximize);
    buttons->addWidget(close);
    layout->addLayout(buttons);
    return bar;
  }

  QWidget *buildSystemStatus()
  {
    auto *box = new QGroupBox(QStringLiteral("系统状态"), this);
    box->setFixedHeight(68);
    auto *layout = new QHBoxLayout(box);
    layout->setContentsMargins(12, 5, 12, 7);
    layout->setSpacing(24);
    layout->addWidget(makeStatusItem(
      QStringLiteral("控制器初始化"), controller_dot_, controller_state_));
    layout->addWidget(makeStatusItem(
      QStringLiteral("电机初始化"), motor_dot_, motor_state_));
    layout->addWidget(makeStatusItem(
      QStringLiteral("系统就绪"), ready_dot_, ready_state_));
    layout->addWidget(makeStatusItem(
      QStringLiteral("当前模式: 未选"), mode_dot_, mode_state_, QStringLiteral("#3ea7e8")));
    layout->addStretch();
    clock_ = new QLabel(box);
    clock_->setProperty("role", "muted");
    layout->addWidget(clock_);
    return box;
  }

  QWidget *makeStatusItem(
    const QString &text,
    QLabel *&dot,
    QLabel *&label,
    const QString &color = QStringLiteral("#ef5a57"))
  {
    auto *item = new QWidget(this);
    auto *layout = new QHBoxLayout(item);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(9);
    dot = new QLabel(item);
    dot->setFixedSize(12, 12);
    setDotColor(dot, color);
    label = new QLabel(text, item);
    label->setProperty("role", "statusText");
    layout->addWidget(dot);
    layout->addWidget(label);
    return item;
  }

  QWidget *buildControlPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("控制区"), this);
    box->setFixedWidth(212);
    auto *layout = new QVBoxLayout(box);
    layout->setContentsMargins(12, 10, 12, 12);
    layout->setSpacing(7);

    mode_group_ = new QButtonGroup(this);
    mode_group_->setExclusive(true);

    layout->addWidget(makeCaption(QStringLiteral("状态与预设")));
    mode_display_ = new QPushButton(QStringLiteral("未选状态"), box);
    mode_display_->setProperty("role", "modeDisplay");
    mode_display_->setFocusPolicy(Qt::NoFocus);
    mode_display_->setAttribute(Qt::WA_TransparentForMouseEvents);
    layout->addWidget(mode_display_);
    layout->addWidget(addModeButton(QStringLiteral("左手初始位置"), kLeftPreset));
    layout->addWidget(addModeButton(QStringLiteral("右手初始位置"), kRightPreset));

    layout->addWidget(makeCaption(QStringLiteral("零力控制")));
    layout->addWidget(addModeButton(QStringLiteral("左臂零力模式"), kLeftZeroForce));
    layout->addWidget(addModeButton(QStringLiteral("右臂零力模式"), kRightZeroForce));
    layout->addWidget(addModeButton(QStringLiteral("双臂零力模式"), kBilateralZeroForce));

    layout->addWidget(makeCaption(QStringLiteral("系统控制")));
    layout->addWidget(addModeButton(QStringLiteral("空闲 / 停止"), kIdle));
    auto *stop = new QPushButton(QStringLiteral("安全停止"), box);
    stop->setProperty("role", "danger");
    connect(stop, &QPushButton::clicked, this, [this] {
      publishCommand(kSsvep, debug_selected_, 0, true);
      appendLog(QStringLiteral("已发送高优先级安全停止"));
    });
    layout->addWidget(stop);
    layout->addStretch();
    return box;
  }

  QWidget *buildSsvepPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("脑电控制区"), this);
    box->setFixedWidth(224);
    auto *layout = new QVBoxLayout(box);
    layout->setContentsMargins(12, 10, 12, 12);
    layout->setSpacing(7);

    layout->addWidget(makeCaption(QStringLiteral("运行方式")));
    debug_button_ = makeBrainButton(QStringLiteral("调试模式"));
    real_button_ = makeBrainButton(QStringLiteral("实机模式"));
    debug_button_->setCheckable(true);
    real_button_->setCheckable(true);
    debug_button_->setChecked(true);
    auto *run_group = new QButtonGroup(this);
    run_group->setExclusive(true);
    run_group->addButton(debug_button_);
    run_group->addButton(real_button_);
    connect(debug_button_, &QPushButton::clicked, this, [this] {
      debug_selected_ = true;
      setDebugButtonsEnabled(true);
      publishCommand(kSsvep, true, 0, false);
    });
    connect(real_button_, &QPushButton::clicked, this, [this] {
      debug_selected_ = false;
      setDebugButtonsEnabled(false);
      publishCommand(kSsvep, false, 0, false);
    });
    layout->addWidget(debug_button_);
    layout->addWidget(real_button_);

    auto *enter = makeBrainButton(QStringLiteral("进入脑电控制"));
    enter->setCheckable(true);
    mode_group_->addButton(enter, kSsvep);
    connect(enter, &QPushButton::clicked, this, [this] {
      publishCommand(kSsvep, debug_selected_, 0, false);
    });
    layout->addWidget(enter);

    layout->addWidget(makeCaption(QStringLiteral("调试动作")));
    addDebugTarget(layout, QStringLiteral("左肩 · joint3"), 1);
    addDebugTarget(layout, QStringLiteral("右肩 · joint13"), 2);
    addDebugTarget(layout, QStringLiteral("左肘 · joint6"), 3);
    addDebugTarget(layout, QStringLiteral("右肘 · joint16"), 4);
    addDebugTarget(layout, QStringLiteral("0 号结果 / 解锁"), 0);

    auto *hint = new QLabel(
      QStringLiteral("调试按钮只在调试模式生效；实机动作仅由串口 EEG 结果触发。"), box);
    hint->setProperty("role", "muted");
    hint->setWordWrap(true);
    layout->addWidget(hint);
    layout->addStretch();
    return box;
  }

  QWidget *buildJointPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("关节状态"), this);
    auto *layout = new QHBoxLayout(box);
    layout->setContentsMargins(9, 10, 9, 9);
    layout->setSpacing(10);
    layout->addWidget(buildJointTable(QStringLiteral("左臂关节"), QStringLiteral("L"), left_table_));
    layout->addWidget(buildJointTable(QStringLiteral("右臂关节"), QStringLiteral("R"), right_table_));
    return box;
  }

  QWidget *buildJointTable(
    const QString &title_text,
    const QString &axis_prefix,
    QTableWidget *&table)
  {
    auto *panel = new QFrame(this);
    panel->setProperty("panel", "sensor");
    auto *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(4);
    auto *title = new QLabel(title_text, panel);
    title->setProperty("role", "sectionTitle");
    layout->addWidget(title);

    table = new QTableWidget(7, 5, panel);
    table->setHorizontalHeaderLabels({
      QStringLiteral("轴号"), QStringLiteral("位置(deg)"), QStringLiteral("速度(deg/s)"),
      QStringLiteral("力矩(Nm)"), QStringLiteral("使能")});
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setMinimumSectionSize(55);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setAlternatingRowColors(true);
    table->setFocusPolicy(Qt::NoFocus);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    for (int row = 0; row < 7; ++row)
    {
      table->setRowHeight(row, 29);
      for (int column = 0; column < 5; ++column)
      {
        const QString value = column == 0 ? axis_prefix + QString::number(row + 1) : QStringLiteral("--");
        auto *item = new QTableWidgetItem(value);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, column, item);
      }
    }
    layout->addWidget(table);
    return panel;
  }

  QWidget *buildForcePanel()
  {
    auto *box = new QGroupBox(QStringLiteral("六维力信息"), this);
    auto *layout = new QGridLayout(box);
    layout->setContentsMargins(9, 10, 9, 9);
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(6);
    layout->addWidget(buildSensorCard(QStringLiteral("右手传感器"), 0), 0, 0);
    layout->addWidget(buildSensorCard(QStringLiteral("右臂传感器"), 6), 0, 1);
    layout->addWidget(buildSensorCard(QStringLiteral("左手传感器"), 12), 1, 0);
    layout->addWidget(buildSensorCard(QStringLiteral("左臂传感器"), 18), 1, 1);
    return box;
  }

  QWidget *buildSensorCard(const QString &title_text, int offset)
  {
    auto *card = new QFrame(this);
    card->setProperty("panel", "sensor");
    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(6, 3, 6, 4);
    layout->setSpacing(2);
    auto *title = new QLabel(title_text, card);
    title->setProperty("role", "sectionTitle");
    layout->addWidget(title);
    auto *values = new QGridLayout;
    values->setContentsMargins(0, 0, 0, 0);
    values->setHorizontalSpacing(8);
    values->setVerticalSpacing(2);
    static const std::array<const char *, 6> names{{"Fx", "Fy", "Fz", "Mx", "My", "Mz"}};
    for (int i = 0; i < 6; ++i)
    {
      force_values_[offset + i] = new QLabel(
        QString::fromLatin1(names[i]) + QStringLiteral(": --"), card);
      force_values_[offset + i]->setProperty("role", "forceValue");
      values->addWidget(force_values_[offset + i], i / 2, i % 2);
    }
    layout->addLayout(values);
    return card;
  }

  QWidget *buildActionPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("脑电动作状态"), this);
    auto *layout = new QGridLayout(box);
    layout->setContentsMargins(9, 10, 9, 8);
    layout->setHorizontalSpacing(8);
    layout->setVerticalSpacing(5);
    phase_ = addInfoTile(layout, 0, 0, QStringLiteral("阶段"));
    target_ = addInfoTile(layout, 0, 1, QStringLiteral("当前动作"));
    execution_mode_ = addInfoTile(layout, 0, 2, QStringLiteral("执行方式"));
    accept_ = addInfoTile(layout, 0, 3, QStringLiteral("允许下一动作"));
    start_angle_ = addInfoTile(layout, 1, 0, QStringLiteral("起点"));
    target_angle_ = addInfoTile(layout, 1, 1, QStringLiteral("目标"));
    actual_angle_ = addInfoTile(layout, 1, 2, QStringLiteral("当前角度"));
    detail_ = addInfoTile(layout, 1, 3, QStringLiteral("状态说明"));
    return box;
  }

  QWidget *buildSerialPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("串口信息（ROS 2 订阅）"), this);
    auto *layout = new QGridLayout(box);
    layout->setContentsMargins(9, 10, 9, 8);
    layout->setHorizontalSpacing(8);
    layout->setVerticalSpacing(5);
    serial_connection_ = addInfoTile(layout, 0, 0, QStringLiteral("连接状态"));
    serial_device_ = addInfoTile(layout, 0, 1, QStringLiteral("设备 / 波特率"));
    serial_status_ = addInfoTile(layout, 0, 2, QStringLiteral("解析状态"));
    sequence_ = addInfoTile(layout, 0, 3, QStringLiteral("序号"));
    source_target_ = addInfoTile(layout, 1, 0, QStringLiteral("来源 / 目标"));
    frequency_ = addInfoTile(layout, 1, 1, QStringLiteral("频率"));
    raw_ = addInfoTile(layout, 1, 2, QStringLiteral("原始帧"), 2);
    raw_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    return box;
  }

  QWidget *buildLogPanel()
  {
    auto *box = new QGroupBox(QStringLiteral("日志"), this);
    auto *layout = new QVBoxLayout(box);
    layout->setContentsMargins(9, 10, 9, 8);
    log_ = new QPlainTextEdit(box);
    log_->setReadOnly(true);
    log_->setMaximumBlockCount(500);
    layout->addWidget(log_);
    return box;
  }

  QLabel *makeCaption(const QString &text)
  {
    auto *label = new QLabel(text, this);
    label->setProperty("role", "caption");
    return label;
  }

  QPushButton *addModeButton(const QString &text, int mode)
  {
    auto *button = new QPushButton(text, this);
    button->setCheckable(true);
    mode_group_->addButton(button, mode);
    connect(button, &QPushButton::clicked, this, [this, mode] {
      publishCommand(mode, false, 0, false);
    });
    return button;
  }

  QPushButton *makeBrainButton(const QString &text)
  {
    auto *button = new QPushButton(text, this);
    button->setProperty("role", "brain");
    return button;
  }

  void addDebugTarget(QVBoxLayout *layout, const QString &text, std::uint8_t target)
  {
    auto *button = makeBrainButton(text);
    connect(button, &QPushButton::clicked, this, [this, target] {
      if (!debug_selected_)
      {
        appendLog(QStringLiteral("实机模式忽略 GUI 调试按钮"));
        return;
      }
      publishCommand(kSsvep, true, target, false);
    });
    debug_target_buttons_.push_back(button);
    layout->addWidget(button);
  }

  QLabel *addInfoTile(
    QGridLayout *layout,
    int row,
    int column,
    const QString &caption,
    int column_span = 1)
  {
    auto *tile = new QFrame(this);
    tile->setProperty("panel", "tile");
    auto *tile_layout = new QVBoxLayout(tile);
    tile_layout->setContentsMargins(6, 3, 6, 4);
    tile_layout->setSpacing(1);
    auto *title = new QLabel(caption, tile);
    title->setProperty("role", "caption");
    auto *value = new QLabel(QStringLiteral("--"), tile);
    value->setProperty("role", "value");
    value->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    value->setMinimumWidth(0);
    tile_layout->addWidget(title);
    tile_layout->addWidget(value);
    layout->addWidget(tile, row, column, 1, column_span);
    return value;
  }

  void publishCommand(int mode, bool debug, std::uint8_t target, bool emergency)
  {
    if (!rclcpp::ok())
    {
      return;
    }
    upperlimb_robot::msg::ControlCommand message;
    message.command = mode;
    message.ssvep_debug = debug;
    message.ssvep_test_target = target;
    message.emergency_stop = emergency;
    command_pub_->publish(message);

    if (!emergency)
    {
      setCurrentMode(mode);
    }
    appendLog(QStringLiteral("发布命令 mode=%1 debug=%2 target=%3 emergency=%4")
      .arg(mode).arg(debug).arg(target).arg(emergency));
  }

  void setCurrentMode(int mode)
  {
    QString text;
    switch (mode)
    {
      case kIdle: text = QStringLiteral("空闲"); break;
      case kLeftPreset: text = QStringLiteral("左手初始位置"); break;
      case kRightPreset: text = QStringLiteral("右手初始位置"); break;
      case kLeftZeroForce: text = QStringLiteral("左臂零力"); break;
      case kRightZeroForce: text = QStringLiteral("右臂零力"); break;
      case kBilateralZeroForce: text = QStringLiteral("双臂零力"); break;
      case kSsvep: text = debug_selected_ ? QStringLiteral("脑电·调试") : QStringLiteral("脑电·实机"); break;
      default: text = QStringLiteral("未知"); break;
    }
    if (mode_group_ != nullptr && mode_group_->button(mode) != nullptr)
    {
      mode_group_->button(mode)->setChecked(true);
    }
    mode_display_->setText(text);
    mode_state_->setText(QStringLiteral("当前模式: ") + text);
  }

  void setDebugButtonsEnabled(bool enabled)
  {
    for (auto *button : debug_target_buttons_)
    {
      button->setEnabled(enabled);
    }
  }

  static void setDotColor(QLabel *dot, const QString &color)
  {
    dot->setStyleSheet(QStringLiteral("background:%1;border-radius:6px;").arg(color));
  }

  static QString targetText(std::uint8_t value)
  {
    static const QStringList values{
      QStringLiteral("无目标"), QStringLiteral("左肩"), QStringLiteral("右肩"),
      QStringLiteral("左肘"), QStringLiteral("右肘")};
    return value < values.size() ? values[value] : QStringLiteral("非法目标");
  }

  static QString phaseText(std::uint8_t value)
  {
    static const QStringList values{
      QStringLiteral("零力"), QStringLiteral("就绪"), QStringLiteral("切换"),
      QStringLiteral("去程"), QStringLiteral("返程"), QStringLiteral("稳定"),
      QStringLiteral("恢复零力"), QStringLiteral("故障")};
    return value < values.size() ? values[value] : QStringLiteral("未知");
  }

  static QString resultText(std::uint8_t value)
  {
    static const QStringList values{
      QStringLiteral("接受"), QStringLiteral("格式错误"), QStringLiteral("重复序号"),
      QStringLiteral("旧序号"), QStringLiteral("超长帧"), QStringLiteral("串口异常"),
      QStringLiteral("忙碌丢弃"), QStringLiteral("串口已连接"), QStringLiteral("串口未配置")};
    return value < values.size() ? values[value] : QStringLiteral("未知");
  }

  void appendLog(const QString &text)
  {
    if (log_ == nullptr)
    {
      return;
    }
    log_->appendPlainText(
      QDateTime::currentDateTime().toString(QStringLiteral("[HH:mm:ss] ")) + text);
  }

  void updateJointTable(QTableWidget *table, std::size_t first_index)
  {
    for (std::size_t row = 0; row < 7; ++row)
    {
      const std::size_t index = first_index + row;
      table->item(static_cast<int>(row), 1)->setText(
        index < robot_.position.size() ? QString::number(robot_.position[index], 'f', 2) : QStringLiteral("--"));
      table->item(static_cast<int>(row), 2)->setText(
        index < robot_.velocity.size() ? QString::number(robot_.velocity[index], 'f', 2) : QStringLiteral("--"));
      table->item(static_cast<int>(row), 3)->setText(
        index < robot_.torque.size() ? QString::number(robot_.torque[index], 'f', 2) : QStringLiteral("--"));
      table->item(static_cast<int>(row), 4)->setText(
        index < robot_.enabled.size() ? (robot_.enabled[index] ? QStringLiteral("是") : QStringLiteral("否"))
                                      : QStringLiteral("--"));
    }
  }

  void updateForceValues()
  {
    static const std::array<const char *, 6> names{{"Fx", "Fy", "Fz", "Mx", "My", "Mz"}};
    for (std::size_t i = 0; i < force_values_.size(); ++i)
    {
      const QString unit = (i % 6) < 3 ? QStringLiteral(" N") : QStringLiteral(" Nm");
      const QString value = i < robot_.force_sensor.size()
        ? QString::number(robot_.force_sensor[i], 'f', 2) + unit
        : QStringLiteral("--");
      force_values_[i]->setText(QString::fromLatin1(names[i % 6]) + QStringLiteral(": ") + value);
    }
  }

  void refresh()
  {
    if (!rclcpp::ok())
    {
      QApplication::quit();
      return;
    }
    clock_->setText(QDateTime::currentDateTime().toString(QStringLiteral("yyyy-MM-dd HH:mm:ss")));

    QMutexLocker lock(&mutex_);
    if (system_pending_)
    {
      controller_state_->setText(system_.controller_init ? QStringLiteral("控制器已初始化") : QStringLiteral("控制器未初始化"));
      motor_state_->setText(system_.joint_init ? QStringLiteral("电机已初始化") : QStringLiteral("电机未初始化"));
      ready_state_->setText(system_.system_ready ? QStringLiteral("系统已就绪") : QStringLiteral("系统未就绪"));
      setDotColor(controller_dot_, system_.controller_init ? QStringLiteral("#52c940") : QStringLiteral("#ef5a57"));
      setDotColor(motor_dot_, system_.joint_init ? QStringLiteral("#52c940") : QStringLiteral("#ef5a57"));
      setDotColor(ready_dot_, system_.system_ready ? QStringLiteral("#52c940") : QStringLiteral("#ef5a57"));
      system_pending_ = false;
    }
    if (robot_pending_)
    {
      updateJointTable(left_table_, 10);
      updateJointTable(right_table_, 0);
      updateForceValues();
      robot_pending_ = false;
    }
    if (result_pending_)
    {
      serial_connection_->setText(result_.serial_connected ? QStringLiteral("已连接") : QStringLiteral("未连接"));
      const QString device = QString::fromStdString(result_.serial_device);
      serial_device_->setText(
        (device.isEmpty() ? QStringLiteral("未配置") : device) +
        QStringLiteral(" / ") + QString::number(result_.baud_rate));
      serial_status_->setText(resultText(result_.status) + QStringLiteral(": ") + QString::fromStdString(result_.detail));
      sequence_->setText(QString::number(result_.sequence));
      source_target_->setText(QString::fromStdString(result_.source) + QStringLiteral(" / ") + targetText(result_.target));
      frequency_->setText(QString::number(result_.frequency_hz, 'f', 2) + QStringLiteral(" Hz"));
      raw_->setText(QString::fromStdString(result_.raw).isEmpty() ? QStringLiteral("--") : QString::fromStdString(result_.raw));
      appendLog(QStringLiteral("串口: ") + serial_status_->text());
      result_pending_ = false;
    }
    if (action_pending_)
    {
      phase_->setText(phaseText(action_.phase));
      target_->setText(targetText(action_.target));
      accept_->setText(action_.ready_for_command ? QStringLiteral("是") : QStringLiteral("否"));
      execution_mode_->setText(action_.debug_mode ? QStringLiteral("调试") : QStringLiteral("实机"));
      static const std::array<int, 5> target_axis{{-1, 12, 2, 15, 5}};
      const int axis = action_.target < target_axis.size() ? target_axis[action_.target] : -1;
      if (axis >= 0 && static_cast<std::size_t>(axis) < action_.q0_deg.size() &&
          static_cast<std::size_t>(axis) < action_.target_deg.size() &&
          static_cast<std::size_t>(axis) < action_.actual_deg.size())
      {
        const QString suffix = QStringLiteral("° / idx %1").arg(axis);
        start_angle_->setText(QString::number(action_.q0_deg[axis], 'f', 2) + suffix);
        target_angle_->setText(QString::number(action_.target_deg[axis], 'f', 2) + suffix);
        actual_angle_->setText(QString::number(action_.actual_deg[axis], 'f', 2) + suffix);
      }
      else
      {
        start_angle_->setText(QStringLiteral("--"));
        target_angle_->setText(QStringLiteral("--"));
        actual_angle_->setText(QStringLiteral("--"));
      }
      detail_->setText(QString::fromStdString(action_.detail));
      action_pending_ = false;
    }
  }

  rclcpp::Node::SharedPtr node_;
  rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
  std::thread spin_thread_;
  rclcpp::Publisher<upperlimb_robot::msg::ControlCommand>::SharedPtr command_pub_;
  rclcpp::Subscription<upperlimb_robot::msg::SystemState>::SharedPtr system_sub_;
  rclcpp::Subscription<upperlimb_robot::msg::RobotState>::SharedPtr robot_sub_;
  rclcpp::Subscription<upperlimb_robot::msg::SsvepResult>::SharedPtr result_sub_;
  rclcpp::Subscription<upperlimb_robot::msg::SsvepActionStatus>::SharedPtr action_sub_;

  QMutex mutex_;
  upperlimb_robot::msg::SystemState system_;
  upperlimb_robot::msg::RobotState robot_;
  upperlimb_robot::msg::SsvepResult result_;
  upperlimb_robot::msg::SsvepActionStatus action_;
  bool system_pending_{false};
  bool robot_pending_{false};
  bool result_pending_{false};
  bool action_pending_{false};
  bool debug_selected_{true};

  QButtonGroup *mode_group_{nullptr};
  std::vector<QPushButton *> debug_target_buttons_;
  QPushButton *mode_display_{nullptr};
  QPushButton *debug_button_{nullptr};
  QPushButton *real_button_{nullptr};

  QLabel *controller_dot_{nullptr};
  QLabel *motor_dot_{nullptr};
  QLabel *ready_dot_{nullptr};
  QLabel *mode_dot_{nullptr};
  QLabel *controller_state_{nullptr};
  QLabel *motor_state_{nullptr};
  QLabel *ready_state_{nullptr};
  QLabel *mode_state_{nullptr};
  QLabel *clock_{nullptr};

  QTableWidget *left_table_{nullptr};
  QTableWidget *right_table_{nullptr};
  std::array<QLabel *, 24> force_values_{};

  QLabel *phase_{nullptr};
  QLabel *target_{nullptr};
  QLabel *accept_{nullptr};
  QLabel *execution_mode_{nullptr};
  QLabel *detail_{nullptr};
  QLabel *start_angle_{nullptr};
  QLabel *target_angle_{nullptr};
  QLabel *actual_angle_{nullptr};

  QLabel *serial_status_{nullptr};
  QLabel *serial_connection_{nullptr};
  QLabel *serial_device_{nullptr};
  QLabel *sequence_{nullptr};
  QLabel *source_target_{nullptr};
  QLabel *frequency_{nullptr};
  QLabel *raw_{nullptr};
  QPlainTextEdit *log_{nullptr};
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  QApplication application(argc, argv);
  application.setApplicationName(QStringLiteral("UpperLimb GUI"));
  SsvepGui window;
  window.show();
  const int result = application.exec();
  rclcpp::shutdown();
  return result;
}

#include "main.moc"
