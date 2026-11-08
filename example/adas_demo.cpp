#include "Executor.hpp"

#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    std::unique_ptr<adas::Executor> executor(adas::Executor::NewExecutor());
    if (!executor)
    {
        std::cerr << "Unable to create executor\n";
        return 1;
    }
    executor->Execute(argc > 1 ? argv[1] : "FMLMLM");
    const auto pose = executor->Query();
    std::cout << '(' << pose.x << ", " << pose.y << ", " << pose.heading << ")\n";
    return 0;
}
