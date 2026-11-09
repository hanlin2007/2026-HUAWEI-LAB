#include <gtest/gtest.h>
#include <functional>
#include "../src/Command.hpp"
#include "PoseEq.hpp"

namespace adas {
TEST(CommandTest, function_owns_a_copy_after_source_object_is_destroyed) {
    std::function<void(PoseHandler&)> command;
    {
        const MoveCommand temporary;
        command = temporary;
    }
    PoseHandler pose{{4, -2, 'W'}};
    command(pose);
    const Pose target{3, -2, 'W'};
    EXPECT_EQ(target, pose.Query());
}
TEST(CommandTest, stateless_functor_keeps_vehicle_states_independent) {
    const std::function<void(PoseHandler&)> move = MoveCommand{};
    PoseHandler first{{0, 0, 'E'}};
    PoseHandler second{{0, 0, 'N'}};
    FastCommand{}(first);
    move(first);
    move(second);
    const Pose firstTarget{2, 0, 'E'};
    const Pose secondTarget{0, 1, 'N'};
    EXPECT_EQ(firstTarget, first.Query());
    EXPECT_EQ(secondTarget, second.Query());
}
} // namespace adas
