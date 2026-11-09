#pragma once

#include "PoseHandler.hpp"

namespace adas {

    class MoveCommand final
    {
    public:
        void operator()(PoseHandler& executor) const noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.Move();
        }
    };

    class TurnLeftCommand final
    {
    public:
        void operator()(PoseHandler& executor) const noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final
    {
    public:
        void operator()(PoseHandler& executor) const noexcept
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnRight();
        }
    };

    class FastCommand final
    {
    public:
        void operator()(PoseHandler& executor) const noexcept
        {
            executor.Fast();
        }
    };

} // namespace adas
