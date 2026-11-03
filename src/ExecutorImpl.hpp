#pragma once

#include "../include/Executor.hpp"
#include <string>

namespace adas {

// Executor 的具体实现
class ExecutorImpl : public Executor
{
public:
    explicit ExecutorImpl(const Pose &pose) noexcept;
    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl &) = delete;
    ExecutorImpl &operator=(const ExecutorImpl &) = delete;

public:
    Pose Query(void) const noexcept override;

private:
    Pose pose;
};

} // namespace adas
