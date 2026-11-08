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
    class ICommand
    {
    public:
        virtual ~ICommand() = default;
        virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
    };

    class MoveCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.Move();
        }
    };

    class TurnLeftCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnLeft();
        }
    };

    class TurnRightCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast())
            {
                executor.Move();
            }
            executor.TurnRight();
        }
    };

    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.Fast();
        }
    };

    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;

    Pose pose;
    bool fast{false};
};

} // namespace adas
