#include "ExecutorImpl.hpp"
#include "Command.hpp"

#include <new>
#include <functional>
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
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;
    const MoveCommand move;
    const TurnLeftCommand left;
    const TurnRightCommand right;
    const FastCommand fast;
    cmderMap.emplace('M', move.operate);
    cmderMap.emplace('L', left.operate);
    cmderMap.emplace('R', right.operate);
    cmderMap.emplace('F', fast.operate);
    for (const auto cmd : commands)
    {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end())
        {
            it->second(poseHandler);
        }
    }
}

} // namespace adas
