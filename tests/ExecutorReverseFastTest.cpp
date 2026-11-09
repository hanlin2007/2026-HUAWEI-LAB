#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {
TEST(ExecutorReverseFastTest, FBM_moves_back_two) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("FBM");
    // then
    const Pose target{-2, 0, 'E'};
    EXPECT_EQ(target, executor->Query());
}
TEST(ExecutorReverseFastTest, FBL_moves_back_then_turns_right) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("FBL");
    // then
    const Pose target{-1, 0, 'S'};
    EXPECT_EQ(target, executor->Query());
}
TEST(ExecutorReverseFastTest, FBR_moves_back_then_turns_left) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("FBR");
    // then
    const Pose target{-1, 0, 'N'};
    EXPECT_EQ(target, executor->Query());
}
} // namespace adas
