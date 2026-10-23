#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

#include "upperlimb_robot/control_algorithms.hpp"

namespace
{

using upperlimb_robot::AXIS_NUM;
using upperlimb_robot::ControlOutputCache;
using upperlimb_robot::MotorStateCache;
using upperlimb_robot::SensorStateCache;
using upperlimb_robot::SsvepControl;
using upperlimb_robot::SsvepPhase;

void applySimulatedPosition(
    const ControlOutputCache &output,
    MotorStateCache &state)
{
  for (std::size_t i = 0; i < AXIS_NUM; ++i)
  {
    if (output.use_position[i])
    {
      state.position[i] = output.target_position[i];
    }
    state.velocity[i] = 0.0;
  }
}

bool runUntilReadyAfterMotion(
    SsvepControl &control,
    MotorStateCache &state)
{
  SensorStateCache sensors;
  for (int cycle = 0; cycle < 500; ++cycle)
  {
    ControlOutputCache output;
    control.run(state, sensors, 0.02, output);
    applySimulatedPosition(output, state);

    const auto &status = control.status();
    if (status.phase == SsvepPhase::Fault)
    {
      return false;
    }
    if (status.phase == SsvepPhase::Ready && status.target == 0 &&
        status.detail.find("往返完成") != std::string::npos)
    {
      return true;
    }
  }
  return false;
}

TEST(SsvepControlTest, MapsAllFourTargetsToConfirmedJoints)
{
  constexpr std::array<int, 5> expected_axis = {-1, 12, 2, 15, 5};

  for (std::uint8_t target = 1; target <= 4; ++target)
  {
    SsvepControl control;
    MotorStateCache state;
    for (std::size_t i = 0; i < AXIS_NUM; ++i)
    {
      state.position[i] = static_cast<double>(i) * 0.1;
    }

    control.reset(true);
    std::string reason;
    ASSERT_TRUE(control.requestTarget(target, state, reason)) << reason;

    const auto &status = control.status();
    const int axis = expected_axis[target];
    EXPECT_EQ(status.target, target);
    EXPECT_EQ(status.phase, SsvepPhase::Switching);
    EXPECT_DOUBLE_EQ(status.q0_deg[axis], state.position[axis]);
    EXPECT_DOUBLE_EQ(
        status.target_deg[axis],
        state.position[axis] + upperlimb_robot::SSVEP_DEBUG_TRAVEL_DEG);

    for (std::size_t i = 0; i < AXIS_NUM; ++i)
    {
      if (static_cast<int>(i) != axis)
      {
        EXPECT_DOUBLE_EQ(status.target_deg[i], state.position[i]);
      }
    }
  }
}

TEST(SsvepControlTest, RejectsOtherTargetsWhileMotionIsLocked)
{
  SsvepControl control;
  MotorStateCache state;
  control.reset(true);

  std::string reason;
  ASSERT_TRUE(control.requestTarget(1, state, reason));
  EXPECT_FALSE(control.requestTarget(4, state, reason));
  EXPECT_NE(reason.find("动作执行中"), std::string::npos);
  EXPECT_EQ(control.status().target, 1);
}

TEST(SsvepControlTest, CompletesRoundTripAndRequiresNeutralToRearm)
{
  SsvepControl control;
  MotorStateCache state;
  control.reset(true);

  std::string reason;
  ASSERT_TRUE(control.requestTarget(3, state, reason));
  ASSERT_TRUE(runUntilReadyAfterMotion(control, state));
  EXPECT_FALSE(control.status().ready_for_command);
  EXPECT_NEAR(state.position[15], 0.0, 1e-9);

  EXPECT_FALSE(control.requestTarget(2, state, reason));
  EXPECT_NE(reason.find("等待0号"), std::string::npos);

  EXPECT_FALSE(control.requestTarget(0, state, reason));
  EXPECT_FALSE(control.status().ready_for_command);

  SensorStateCache sensors;
  for (int cycle = 0; cycle < 70; ++cycle)
  {
    ControlOutputCache output;
    control.run(state, sensors, 0.02, output);
  }
  EXPECT_TRUE(control.status().ready_for_command);
  EXPECT_TRUE(control.requestTarget(2, state, reason));
}

TEST(SsvepControlTest, EmergencyStopAlwaysEntersFault)
{
  SsvepControl control;
  MotorStateCache state;
  control.reset(true);

  std::string reason;
  ASSERT_TRUE(control.requestTarget(2, state, reason));
  control.emergencyStop("测试安全停止");

  EXPECT_EQ(control.status().phase, SsvepPhase::Fault);
  EXPECT_FALSE(control.status().ready_for_command);
  EXPECT_EQ(control.status().target, 0);
  EXPECT_EQ(control.status().detail, "测试安全停止");
}

TEST(SsvepProtocolTest, AcceptsValidFramesAndRejectsDuplicateOrOldSequence)
{
  std::int64_t last_sequence = -1;
  auto result = upperlimb_robot::parseSsvepProtocolFrame(
      "RESULT,42,EEG,3,15.00", last_sequence);
  ASSERT_EQ(result.status, 0);
  EXPECT_EQ(result.sequence, 42u);
  EXPECT_EQ(result.source, "EEG");
  EXPECT_EQ(result.target, 3);
  EXPECT_DOUBLE_EQ(result.frequency_hz, 15.0);
  EXPECT_EQ(last_sequence, 42);

  result = upperlimb_robot::parseSsvepProtocolFrame(
      "RESULT,42,EEG,3,15.00", last_sequence);
  EXPECT_EQ(result.status, 2);

  result = upperlimb_robot::parseSsvepProtocolFrame(
      "RESULT,41,EEG,2,12.00", last_sequence);
  EXPECT_EQ(result.status, 3);
  EXPECT_EQ(last_sequence, 42);

  result = upperlimb_robot::parseSsvepProtocolFrame(
      "RESULT,43,TEST,0,0.00", last_sequence);
  EXPECT_EQ(result.status, 0);
  EXPECT_EQ(result.source, "TEST");
  EXPECT_EQ(last_sequence, 43);
}

TEST(SsvepProtocolTest, StrictlyRejectsMalformedOrOutOfRangeFields)
{
  const std::array<std::string, 9> invalid_frames = {
      "BAD,1,EEG,1,12.00",
      "RESULT,-1,EEG,1,12.00",
      "RESULT,+1,EEG,1,12.00",
      "RESULT,9223372036854775808,EEG,1,12.00",
      "RESULT,1,UNKNOWN,1,12.00",
      "RESULT,1,EEG,5,12.00",
      "RESULT,1,EEG,1,nan",
      "RESULT,1,EEG,1,201.00",
      "RESULT,1,EEG,1, 12.00"};

  for (const auto &frame : invalid_frames)
  {
    std::int64_t last_sequence = -1;
    const auto result = upperlimb_robot::parseSsvepProtocolFrame(
        frame, last_sequence);
    EXPECT_EQ(result.status, 1) << frame;
    EXPECT_EQ(last_sequence, -1) << frame;
  }
}

} // namespace
