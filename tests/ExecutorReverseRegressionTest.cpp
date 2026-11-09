#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas {
struct ReverseCase { const char* name; char heading; const char* commands; Pose target; };
class ReverseDirectionsTest : public testing::TestWithParam<ReverseCase> {};
TEST_P(ReverseDirectionsTest, applies_reverse_in_each_direction) {
    const auto& c = GetParam();
    std::unique_ptr<Executor> executor(Executor::NewExecutor({3, -2, c.heading}));
    ASSERT_NE(nullptr, executor);
    executor->Execute(c.commands);
    EXPECT_EQ(c.target, executor->Query());
}
INSTANTIATE_TEST_SUITE_P(AllDirections, ReverseDirectionsTest, testing::Values(
    ReverseCase{"E_BM", 'E', "BM", {2, -2, 'E'}},
    ReverseCase{"E_BL", 'E', "BL", {3, -2, 'S'}},
    ReverseCase{"E_BR", 'E', "BR", {3, -2, 'N'}},
    ReverseCase{"S_BM", 'S', "BM", {3, -1, 'S'}},
    ReverseCase{"S_BL", 'S', "BL", {3, -2, 'W'}},
    ReverseCase{"S_BR", 'S', "BR", {3, -2, 'E'}},
    ReverseCase{"W_BM", 'W', "BM", {4, -2, 'W'}},
    ReverseCase{"W_BL", 'W', "BL", {3, -2, 'N'}},
    ReverseCase{"W_BR", 'W', "BR", {3, -2, 'S'}},
    ReverseCase{"N_BM", 'N', "BM", {3, -3, 'N'}},
    ReverseCase{"N_BL", 'N', "BL", {3, -2, 'E'}},
    ReverseCase{"N_BR", 'N', "BR", {3, -2, 'W'}},
    ReverseCase{"E_BFM", 'E', "BFM", {1, -2, 'E'}},
    ReverseCase{"E_BFL", 'E', "BFL", {2, -2, 'S'}},
    ReverseCase{"E_BFR", 'E', "BFR", {2, -2, 'N'}},
    ReverseCase{"S_BFM", 'S', "BFM", {3, 0, 'S'}},
    ReverseCase{"S_BFL", 'S', "BFL", {3, -1, 'W'}},
    ReverseCase{"S_BFR", 'S', "BFR", {3, -1, 'E'}},
    ReverseCase{"W_BFM", 'W', "BFM", {5, -2, 'W'}},
    ReverseCase{"W_BFL", 'W', "BFL", {4, -2, 'N'}},
    ReverseCase{"W_BFR", 'W', "BFR", {4, -2, 'S'}},
    ReverseCase{"N_BFM", 'N', "BFM", {3, -4, 'N'}},
    ReverseCase{"N_BFL", 'N', "BFL", {3, -3, 'E'}},
    ReverseCase{"N_BFR", 'N', "BFR", {3, -3, 'W'}}), [](const testing::TestParamInfo<ReverseCase>& info) { return info.param.name; });

TEST(ReverseStateTest, reverse_and_fast_activation_commute) {
    for (const std::string commands : {"M", "L", "R", "MLRM"}) {
        std::unique_ptr<Executor> first(Executor::NewExecutor());
        std::unique_ptr<Executor> second(Executor::NewExecutor());
        ASSERT_NE(nullptr, first);
        ASSERT_NE(nullptr, second);
        first->Execute("BF" + commands);
        second->Execute("FB" + commands);
        EXPECT_EQ(first->Query(), second->Query());
    }
}
TEST(ReverseStateTest, states_persist_across_calls_and_empty_input) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("B"); e->Execute("F"); e->Execute(""); e->Execute("M");
    const Pose target{0, -2, 'N'};
    EXPECT_EQ(target, e->Query());
}
TEST(ReverseStateTest, cancelling_reverse_preserves_fast) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("BFMBM");
    const Pose target{0, 0, 'N'};
    EXPECT_EQ(target, e->Query());
}
TEST(ReverseStateTest, cancelling_fast_preserves_reverse) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("BFMFM");
    const Pose target{0, -3, 'N'};
    EXPECT_EQ(target, e->Query());
}
TEST(ReverseStateTest, unknown_commands_do_not_change_reverse_or_fast) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("BF?m b!M");
    const Pose target{0, -2, 'N'};
    EXPECT_EQ(target, e->Query());
}
TEST(ReverseStateTest, vehicles_keep_reverse_and_fast_independent) {
    std::unique_ptr<Executor> first(Executor::NewExecutor());
    std::unique_ptr<Executor> second(Executor::NewExecutor());
    ASSERT_NE(nullptr, first); ASSERT_NE(nullptr, second);
    first->Execute("BFM"); second->Execute("M");
    const Pose reverse{0, -2, 'N'}, forward{0, 1, 'N'};
    EXPECT_EQ(reverse, first->Query()); EXPECT_EQ(forward, second->Query());
}
TEST(ReverseStateTest, double_toggles_cancel_both_states) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("BFBFM");
    const Pose target{0, 1, 'N'};
    EXPECT_EQ(target, e->Query());
}
TEST(ReverseStateTest, reverse_turns_and_moves_form_closed_square) {
    std::unique_ptr<Executor> e(Executor::NewExecutor());
    ASSERT_NE(nullptr, e);
    e->Execute("BMLMLMLML");
    const Pose target{0, 0, 'N'};
    EXPECT_EQ(target, e->Query());
}
} // namespace adas
