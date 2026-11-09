#include "Point.hpp"
namespace adas {
Point::Point(int x, int y) noexcept : x(x), y(y) {}
Point& Point::operator+=(const Point& rhs) noexcept {
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Point& Point::operator-=(const Point& rhs) noexcept {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
int Point::GetX() const noexcept { return x; }
int Point::GetY() const noexcept { return y; }
} // namespace adas
