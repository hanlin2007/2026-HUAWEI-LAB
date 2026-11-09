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
    // The table owns stateless functors; no command captures an executor.
    static const std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap{
        {'M', MoveCommand{}},
        {'L', TurnLeftCommand{}},
        {'R', TurnRightCommand{}},
        {'F', FastCommand{}},
    };
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
