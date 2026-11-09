#pragma once
#include "Executor.hpp"
#include "Direction.hpp"

namespace adas {
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& pose) noexcept;
    Pose Query() const noexcept;
    void Forward() noexcept;
    void Backward() noexcept;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
    void Reverse() noexcept;
    bool IsReverse() const noexcept;
private:
    Point point;
    const Direction* direction;
    bool fast{false};
    bool reverse{false};
};
} // namespace adas
