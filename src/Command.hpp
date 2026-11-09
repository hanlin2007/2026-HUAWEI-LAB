#pragma once

#include "PoseHandler.hpp"
#include <functional>

namespace adas {

    class MoveCommand final
    {
    public:
        const std::function<void(PoseHandler&)> operate = [](PoseHandler& executor) noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.Move();
        };
    };

    class TurnLeftCommand final
    {
    public:
        const std::function<void(PoseHandler&)> operate = [](PoseHandler& executor) noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnLeft();
        };
    };

    class TurnRightCommand final
    {
    public:
        const std::function<void(PoseHandler&)> operate = [](PoseHandler& executor) noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnRight();
        };
    };

    class FastCommand final
    {
    public:
        const std::function<void(PoseHandler&)> operate = [](PoseHandler& executor) noexcept
        {
            executor.Fast();
        };
    };

} // namespace adas
