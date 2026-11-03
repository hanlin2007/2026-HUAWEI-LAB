#include <gtest/gtest.h>
#include <memory>
#include <tuple>
#include "../include/Executor.hpp"

namespace adas {

bool operator==(const Pose &lhs, const Pose &rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) ==
           std::tie(rhs.x, rhs.y, rhs.heading);
}

TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when / then
    const Pose target{0, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when / then
    const Pose target{0, 0, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    executor->Execute("M");
    const Pose target{1, 0, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));
    executor->Execute("M");
    const Pose target{1, 3, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_plus_1_given_command_is_M_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    executor->Execute("M");
    const Pose target{2, 4, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_y_minus_1_given_command_is_M_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));
    executor->Execute("M");
    const Pose target{2, 2, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_L_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    executor->Execute("L");
    const Pose target{2, 3, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_L_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    executor->Execute("L");
    const Pose target{2, 3, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_L_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));
    executor->Execute("L");
    const Pose target{2, 3, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_L_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));
    executor->Execute("L");
    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_S_given_command_is_R_and_facing_is_E)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    executor->Execute("R");
    const Pose target{2, 3, 'S'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_W_given_command_is_R_and_facing_is_S)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'S'}));
    executor->Execute("R");
    const Pose target{2, 3, 'W'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_N_given_command_is_R_and_facing_is_W)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'W'}));
    executor->Execute("R");
    const Pose target{2, 3, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_facing_E_given_command_is_R_and_facing_is_N)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'N'}));
    executor->Execute("R");
    const Pose target{2, 3, 'E'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_execute_combined_commands_in_order)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    executor->Execute("MLMMRM");
    const Pose target{-2, 2, 'N'};
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_preserve_pose_for_empty_commands_and_continue_across_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({2, 3, 'E'}));
    executor->Execute("");
    const Pose initial{2, 3, 'E'};
    ASSERT_EQ(initial, executor->Query());

    executor->Execute("LM");
    executor->Execute("RM");
    const Pose target{3, 4, 'E'};
    ASSERT_EQ(target, executor->Query());
}

} // namespace adas
