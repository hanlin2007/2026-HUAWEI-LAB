#pragma once
#include "Executor.hpp"

namespace adas {
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& pose) noexcept;
    Pose Query() const noexcept;
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;
private:
    Pose pose;
    bool fast{false};
};
} // namespace adas
