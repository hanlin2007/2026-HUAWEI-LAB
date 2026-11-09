#include <gtest/gtest.h>
#include "../src/Direction.hpp"

namespace adas {
TEST(PointTest, compound_addition_returns_self_and_preserves_operand) {
    Point point{3, -4};
    const Point delta{-2, 5};
    EXPECT_EQ(&point, &(point += delta));
    EXPECT_EQ(1, point.GetX());
    EXPECT_EQ(1, point.GetY());
    EXPECT_EQ(-2, delta.GetX());
    EXPECT_EQ(5, delta.GetY());
    Point copy{point};
    copy = delta;
    EXPECT_EQ(-2, copy.GetX());
    EXPECT_EQ(1, point.GetX());
}
TEST(DirectionTest, all_directions_use_matching_steps_and_turns) {
    const char headings[] = {'E', 'S', 'W', 'N'};
    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, -1, 0, 1};
    for (unsigned i = 0; i < 4; ++i) {
        SCOPED_TRACE(headings[i]);
        const auto& d = Direction::GetDirection(headings[i]);
        EXPECT_EQ(dx[i], d.Move().GetX());
        EXPECT_EQ(dy[i], d.Move().GetY());
        EXPECT_EQ(headings[(i + 3) % 4], d.LeftOne().GetHeading());
        EXPECT_EQ(headings[(i + 1) % 4], d.RightOne().GetHeading());
        EXPECT_EQ(&d, &d.LeftOne().RightOne());
        EXPECT_EQ(&d, &d.RightOne().RightOne().RightOne().RightOne());
    }
}
TEST(DirectionTest, unknown_heading_defaults_to_north) {
    EXPECT_EQ('N', Direction::GetDirection('?').GetHeading());
}
} // namespace adas
