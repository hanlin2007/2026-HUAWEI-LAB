#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {
namespace {
struct FastCase
{
    char heading;
    const char* commands;
    Pose expected;
};

class ExecutorFastDirectionTest : public testing::TestWithParam<FastCase> {};

TEST_P(ExecutorFastDirectionTest, should_apply_fast_command_in_each_direction)
{
    const auto& input = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, input.heading}));
    ASSERT_NE(nullptr, executor);
    executor->Execute(input.commands);
    EXPECT_EQ(input.expected, executor->Query());
}

// Explicit expected poses cover M/L/R x N/E/S/W, including move-before-turn order.
INSTANTIATE_TEST_SUITE_P(AllDirections, ExecutorFastDirectionTest, testing::Values(
    FastCase{'N', "FM", {2, 5, 'N'}},
    FastCase{'E', "FM", {4, 3, 'E'}},
    FastCase{'S', "FM", {2, 1, 'S'}},
    FastCase{'W', "FM", {0, 3, 'W'}},
    FastCase{'N', "FL", {2, 4, 'W'}},
    FastCase{'E', "FL", {3, 3, 'N'}},
    FastCase{'S', "FL", {2, 2, 'E'}},
    FastCase{'W', "FL", {1, 3, 'S'}},
    FastCase{'N', "FR", {2, 4, 'E'}},
    FastCase{'E', "FR", {3, 3, 'S'}},
    FastCase{'S', "FR", {2, 2, 'W'}},
    FastCase{'W', "FR", {1, 3, 'N'}}));
} // namespace

TEST(ExecutorFastRegressionTest, should_preserve_pose_when_only_toggling_fast)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({-2, 3, 'W'}));
    ASSERT_NE(nullptr, executor);
    const Pose initial{-2, 3, 'W'};
    executor->Execute("F");
    EXPECT_EQ(initial, executor->Query());
    executor->Execute("F");
    EXPECT_EQ(initial, executor->Query());
}

TEST(ExecutorFastRegressionTest, should_keep_fast_across_calls_and_empty_commands)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor);
    executor->Execute("F");
    executor->Execute("");
    executor->Execute("M");
    executor->Execute("L");
    executor->Execute("M");
    const Pose fastTarget{-2, 3, 'W'};
    EXPECT_EQ(fastTarget, executor->Query());
    executor->Execute("F");
    executor->Execute("RM");
    const Pose normalTarget{-2, 4, 'N'};
    EXPECT_EQ(normalTarget, executor->Query());
}

TEST(ExecutorFastRegressionTest, should_turn_without_moving_after_fast_is_cancelled)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    ASSERT_NE(nullptr, executor);
    executor->Execute("FFL");
    const Pose leftTarget{2, 3, 'N'};
    EXPECT_EQ(leftTarget, executor->Query());
    executor->Execute("FFR");
    const Pose rightTarget{2, 3, 'E'};
    EXPECT_EQ(rightTarget, executor->Query());
}

TEST(ExecutorFastRegressionTest, should_follow_slide_example_FMLMLM)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor);
    executor->Execute("FMLMLM");
    const Pose target{-3, 1, 'S'};
    EXPECT_EQ(target, executor->Query());
}

TEST(ExecutorFastRegressionTest, should_keep_fast_state_independent_between_executors)
{
    std::unique_ptr<Executor> fastExecutor(Executor::NewExecutor());
    std::unique_ptr<Executor> normalExecutor(Executor::NewExecutor());
    ASSERT_NE(nullptr, fastExecutor);
    ASSERT_NE(nullptr, normalExecutor);
    fastExecutor->Execute("FM");
    normalExecutor->Execute("M");
    const Pose fastTarget{0, 2, 'N'};
    const Pose normalTarget{0, 1, 'N'};
    EXPECT_EQ(fastTarget, fastExecutor->Query());
    EXPECT_EQ(normalTarget, normalExecutor->Query());
}

TEST(ExecutorFastRegressionTest, should_enable_fast_again_after_cancelling)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    ASSERT_NE(nullptr, executor);
    executor->Execute("FFM");
    executor->Execute("FMM");
    const Pose target{0, 5, 'N'};
    EXPECT_EQ(target, executor->Query());
}
} // namespace adas
