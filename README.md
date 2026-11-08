# 实验二：面向对象编程（ADAS）

按 `ppt/实验2-面向对象编程（华为）-to学生.pdf` 的 StepbyStep 完成。仓库主分支名为 `main`，对应课件中的 `master`。

## 已实现的指令

初始姿态默认 `(0,0,N)`，也可以通过 `Executor::NewExecutor(pose)` 指定。`Query()` 查询位置和朝向。

| 指令 | 普通状态 | 加速状态 |
| --- | --- | --- |
| M | 前进一格 | 连续调用两次单格 Move，前进两格 |
| L | 原地左转 90° | 先沿原朝向前进一格，再左转 |
| R | 原地右转 90° | 先沿原朝向前进一格，再右转 |
| F | 开启加速 | 取消加速 |

加速状态在多次 `Execute()` 之间保持，每个执行器独立保存状态。空字符串不改变状态。未知指令沿用实验一的忽略行为。

## WSL 构建与运行

在 Ubuntu WSL 中首次准备工具（已安装则跳过）：

```bash
sudo apt update
sudo apt install -y build-essential cmake git
```

进入本机工程（解压到其他位置时修改路径）：

```bash
cd '/mnt/c/Users/lihanlin2007/Desktop/大二上学期/第一阶段/C++程序设计/Lab_HUAWEI'
```

课件对应的脚本命令：

```bash
bash scripts/build.sh
bash scripts/run.sh
```

等价的配置、编译、运行 GTest 命令：

```bash
cmake --preset wsl-debug
cmake --build --preset wsl-debug --parallel
ctest --preset wsl-debug --no-tests=error
./build/wsl-debug/tests/adas_tests
```

只运行课件的四个 F 用例，或列出所有用例：

```bash
./build/wsl-debug/tests/adas_tests --gtest_filter='ExecutorFastTest.*'
./build/wsl-debug/tests/adas_tests --gtest_list_tests
```

运行车辆演示（从默认姿态执行参数中的指令，省略参数默认执行 FMLMLM）：

```bash
./build/wsl-debug/src/adas_demo FMLMLM
# 输出：(-3, 1, S)
```

Google Test 源码随工程提供，构建不需要联网下载依赖。`adas` 是业务静态库，`adas_tests` 是测试程序，`adas_demo` 是演示程序。

## 查看提交及里程碑

查看提交使用 `git log`；`git commit --log` 不是有效命令。

```bash
git status
git branch -avv
git log --graph --decorate --oneline --all
git log --format='%h %ad %s' --date=iso-strict -15
git show HEAD
git log lab1-cleancode-base --oneline
git log lab2-oop-three-features --oneline
git log lab2-oop-support-F --oneline
git diff lab1-cleancode-base..lab2-oop-three-features -- src
git diff lab2-oop-three-features..lab2-oop-support-F -- src tests
```

要复现历史阶段，建议使用独立目录，避免覆盖当前工程：

```bash
git worktree add --detach ../lab2-oop-review lab2-oop-three-features
cd ../lab2-oop-review
bash scripts/build.sh
bash scripts/run.sh
```

## 工程结构

- `include/Executor.hpp`：公开接口与 Pose。
- `src/ExecutorImpl.*`：单格移动、转向、F 状态及嵌套命令类。
- `tests/ExecutorTest.cpp`：实验一 16 个回归用例。
- `tests/ExecutorFastTest.cpp`：课件要求的 4 个 F 用例。
- `tests/ExecutorFastRegressionTest.cpp`：12 个全方向参数用例及 6 个状态/组合用例。
- `tests/PoseEq.*`：测试共用的姿态比较。
- `tests/googletest/`：随工程提供的 Google Test。
- `example/adas_demo.cpp`：车辆指令演示。
- `doc/LAB2.md`：课件步骤与提交里程碑说明。

最终共 38 个测试。课件原计数为 14+4=18；本工程实验一已有额外 2 个组合测试，因此课件阶段为 16+4=20，补充 18 个回归用例后为 38。
