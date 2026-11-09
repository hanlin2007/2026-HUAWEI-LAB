# 实验三：面向对象编程与函数式编程（ADAS）

按 `ppt/实验3-面向对象编程&函数式编程.pdf` 完成。主分支为 `main`（对应课件的 `master`）。

## 实现内容

- 独立 `Command.hpp`，抽取 `PoseHandler` 消除命令与执行器的循环依赖。
- `Point` 封装坐标及 `+=`、`-=`；`Direction` 用 E/S/W/N 数组和模运算完成转向，未知朝向按课件回退为 N。
- 依次完成多态命令表、无捕获 Lambda、`operator()` 函数对象、初始化列表命令表。
- B 倒车及 B/F 正交状态，状态跨 Execute 调用保持，每辆车独立；未知指令忽略。
- Google Test 源码随工程提供，无需联网下载。

## 指令规则

| 指令 | 普通 | F 加速 | B 倒车 | BF 加速倒车 |
| --- | --- | --- | --- | --- |
| M | 前进一格 | 连续前进两次，每次一格 | 后退一格 | 连续后退两次，每次一格 |
| L | 原地左转 | 前进一格后左转 | 原地右转 | 后退一格后右转 |
| R | 原地右转 | 前进一格后右转 | 原地左转 | 后退一格后左转 |

F、B 分别切换各自状态，再次收到同一指令即取消，两种状态互不影响。

## WSL 构建、运行和测试

首次安装工具（已有则跳过）：

```bash
sudo apt update
sudo apt install -y build-essential cmake git
```

在本机工程中操作：

```bash
cd '/mnt/c/Users/lihanlin2007/Desktop/大二上学期/第一阶段/C++程序设计/Lab_HUAWEI'
cmake --preset wsl-debug
cmake --build --preset wsl-debug --parallel
./build/wsl-debug/src/adas_demo BFM
# (0, -2, N)
```

运行全部 GTest（83 项）及 CTest：

```bash
./build/wsl-debug/tests/adas_tests
ctest --preset wsl-debug --no-tests=error
```

只运行课件倒车测试、列出测试、导出 XML：

```bash
./build/wsl-debug/tests/adas_tests --gtest_filter='ExecutorReverseTest.*:ExecutorReverseFastTest.*'
./build/wsl-debug/tests/adas_tests --gtest_list_tests
./build/wsl-debug/tests/adas_tests --gtest_output=xml:build/gtest-results.xml
```

也可使用脚本：

```bash
bash scripts/build.sh
bash scripts/run.sh
```

解压桌面的提交包后，进入解压得到的 `Lab_HUAWEI` 目录，再运行以上命令。压缩包不包含 build 缓存，必须先构建。

## 提交记录与阶段分支

```bash
git log --oneline
git log --graph --decorate --oneline --all
git log --format='%h %ad %s' --date=iso-strict -11
git branch -avv
git status
```

课件指定里程碑（保留课件原拼写 `recfactor`）：

- `lab3-oop-recfactor-final`：命令拆分、状态解耦、表驱动、Point/Direction 抽象完成。
- `lab3-fp`：Lambda、函数对象及表初始化完成。
- `lab3-fp-support-B`：B 与 BF 功能完成，课件及既有 50 项测试通过。
- `main`：完整 83 项测试、验证记录及交付说明。

历史阶段可通过独立目录复现：

```bash
git worktree add --detach ../lab3-oop-review lab3-oop-recfactor-final
cd ../lab3-oop-review
bash scripts/build.sh
bash scripts/run.sh
```

## 测试与工程结构

| 测试文件 | 用例数 | 内容 |
| --- | ---: | --- |
| ExecutorTest.cpp | 16 | 实验一回归 |
| ExecutorFastTest.cpp | 4 | 课件 F 测试 |
| ExecutorFastRegressionTest.cpp | 18 | F 方向与状态回归 |
| StateTypesTest.cpp | 4 | Point 运算、Direction 映射及循环转向 |
| CommandTest.cpp | 2 | 函数对象生命周期、状态隔离 |
| ExecutorReverseTest.cpp | 4 | BM、BL、BR、BBM |
| ExecutorReverseFastTest.cpp | 3 | FBM、FBL、FBR |
| ExecutorReverseRegressionTest.cpp | 32 | B/BF 四方向矩阵、顺序交换、独立取消、跨调用、未知指令、车辆隔离和闭环 |

业务代码在 `include/` 与 `src/`；演示在 `example/`；构建运行脚本在 `scripts/`。
详细课件映射见 `doc/LAB3.md`，真实测试记录见 `doc/validation/lab3/`。实验二说明仍保存在 `doc/LAB2.md`。

仓库：https://github.com/hanlin2007/2026-HUAWEI-LAB
