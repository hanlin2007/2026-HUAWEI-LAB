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

} // namespace adas
