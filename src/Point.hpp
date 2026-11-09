#pragma once
namespace adas {
class Point final {
public:
    Point(int x, int y) noexcept;
    Point(const Point&) noexcept = default;
    Point& operator=(const Point&) noexcept = default;
    Point& operator+=(const Point& rhs) noexcept;
    Point& operator-=(const Point& rhs) noexcept;
    int GetX() const noexcept;
    int GetY() const noexcept;
private:
    int x;
    int y;
};
} // namespace adas
