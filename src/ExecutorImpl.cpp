#include "ExecutorImpl.hpp"
#include "Command.hpp"

#include <new>
#include <memory>

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose &pose) noexcept : poseHandler(pose) {}

Pose ExecutorImpl::Query(void) const noexcept
{
    return poseHandler.Query();
}

Executor *Executor::NewExecutor(const Pose &pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

void ExecutorImpl::Execute(const std::string &commands) noexcept
{
    for (const auto cmd : commands)
    {
        std::unique_ptr<ICommand> cmder;
        if (cmd == 'M')
        {
            cmder = std::make_unique<MoveCommand>();
        }
        else if (cmd == 'L')
        {
            cmder = std::make_unique<TurnLeftCommand>();
        }
        else if (cmd == 'R')
        {
            cmder = std::make_unique<TurnRightCommand>();
        }
        else if (cmd == 'F')
        {
            cmder = std::make_unique<FastCommand>();
        }
        if (cmder)
        {
            cmder->DoOperate(poseHandler);
        }
    }
}

} // namespace adas
