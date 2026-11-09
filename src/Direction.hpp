#pragma once
#include "Point.hpp"
namespace adas {
class Direction final {
public:
    static const Direction& GetDirection(char heading) noexcept;
    Direction(unsigned index, char heading) noexcept;
    const Point& Move() const noexcept;
    const Direction& LeftOne() const noexcept;
    const Direction& RightOne() const noexcept;
    char GetHeading() const noexcept;
private:
    unsigned index;
    char heading;
};
} // namespace adas
