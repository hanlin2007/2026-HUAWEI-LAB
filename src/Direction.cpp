#include "Direction.hpp"
namespace adas {
namespace {
const Direction directions[] = {{0, 'E'}, {1, 'S'}, {2, 'W'}, {3, 'N'}};
const Point points[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
}
Direction::Direction(unsigned index, char heading) noexcept : index(index % 4), heading(heading) {}
const Direction& Direction::GetDirection(char heading) noexcept {
    for (const auto& direction : directions) {
        if (direction.GetHeading() == heading) { return direction; }
    }
    return directions[3];
}
const Point& Direction::Move() const noexcept { return points[index]; }
const Direction& Direction::LeftOne() const noexcept { return directions[(index + 3) % 4]; }
const Direction& Direction::RightOne() const noexcept { return directions[(index + 1) % 4]; }
char Direction::GetHeading() const noexcept { return heading; }
} // namespace adas
