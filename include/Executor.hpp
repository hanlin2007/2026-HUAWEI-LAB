#pragma once
#include <string>
// 使用命名空间组织代码，并防止命名冲突
namespace adas
{
    // 使用结构体，便于数据的组织和传递
    struct Pose{
        int x;
        int y;
        char heading;
    };

    // 抽象类，提供接口定义，隐藏功能实现细节
    class Executor
    {
        public:
        // 细节一：静态成员函数，无需实例化即可调用 Executor::NewExecutor() 通过类名直接调用
        // 细节二：使用默认参数，允许调用者使用默认值， Pose{0,0,'N'} 是一个临时对象
        // 细节三：const Pose& 常量绑定引用
        // 细节四：noexcept 表示函数不会抛出异常，提升性能和安全性，便于编译器优化
        static Executor* NewExecutor(const Pose& pose={0,0,'N'}) noexcept;

        public:
            Executor() = default; // 默认构造函数
            virtual ~Executor() = default; // 虚析构函数，确保派生类析构函数被正确调用

            Executor(const Executor&) = delete; // 禁止拷贝构造函数，防止对象被意外复制
            Executor& operator=(const Executor&) = delete; // 禁止拷贝赋值
            // 如何理解这里移动的构造和赋值也不隐式生成了

        public:
            virtual void Execute(const std::string& command) noexcept = 0;
            virtual Pose Query(void) const noexcept = 0; // 纯虚函数，要求派生类必须实现该方法，const 表示不会修改对象状态
    };
}
