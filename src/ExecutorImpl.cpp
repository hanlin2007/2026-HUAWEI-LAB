#include "ExecutorImpl.hpp"
#include "Command.hpp"

#include <new>
#include <memory>
#include <unordered_map>

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
    const std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap = [] {
        std::unordered_map<char, std::unique_ptr<ICommand>> table;
        table.emplace('M', std::make_unique<MoveCommand>());
        table.emplace('L', std::make_unique<TurnLeftCommand>());
        table.emplace('R', std::make_unique<TurnRightCommand>());
        table.emplace('F', std::make_unique<FastCommand>());
        return table;
    }();
    for (const auto cmd : commands)
    {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            it->second->DoOperate(poseHandler);
        }
    }
}

} // namespace adas
