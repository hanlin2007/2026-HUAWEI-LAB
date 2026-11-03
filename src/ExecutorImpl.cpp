#include "ExecutorImpl.hpp"

#include <new>

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose &initialPose) noexcept : pose{0, 0, 'N'}
{
    (void)initialPose;
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return pose;
}

Executor *Executor::NewExecutor(const Pose &pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

} // namespace adas
