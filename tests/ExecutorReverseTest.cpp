#include <gtest/gtest.h>
#include <memory>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {
TEST(ExecutorReverseTest, BM_moves_back_one) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("BM");
    // then
    const Pose target{-1, 0, 'E'};
    EXPECT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, BL_turns_right) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("BL");
    // then
    const Pose target{0, 0, 'S'};
    EXPECT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, BR_turns_left) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("BR");
    // then
    const Pose target{0, 0, 'N'};
    EXPECT_EQ(target, executor->Query());
}
TEST(ExecutorReverseTest, BBM_cancels_reverse) {
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    ASSERT_NE(nullptr, executor);
    // when
    executor->Execute("BBM");
    // then
    const Pose target{0, 1, 'N'};
    EXPECT_EQ(target, executor->Query());
}
} // namespace adas
