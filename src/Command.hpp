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
            if (executor.IsReverse()) { executor.TurnRight(); }
            else { executor.TurnLeft(); }
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
            if (executor.IsReverse()) { executor.TurnLeft(); }
            else { executor.TurnRight(); }
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

    class ReverseCommand final
    {
    public:
        void operator()(PoseHandler& executor) const noexcept
        {
            executor.Reverse();
        }
    };

} // namespace adas
