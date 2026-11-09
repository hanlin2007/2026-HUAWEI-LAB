#pragma once

#include "../include/Executor.hpp"
#include <string>

namespace adas {

// Executor 的具体实现
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose &pose) noexcept;
    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl &) = delete;
    ExecutorImpl &operator=(const ExecutorImpl &) = delete;

public:
    Pose Query(void) const noexcept override;
    void Execute(const std::string &commands) noexcept override;

private:
public:
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
