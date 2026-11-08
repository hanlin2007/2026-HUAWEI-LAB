# 实验二步骤与验证记录

依据实验二 StepbyStep，保留实验一接口与行为，分阶段完成封装、继承、多态及 F 指令扩展。主开发分支使用仓库现有的 main（课件称 master），三个里程碑分支均只作为阶段快照。

| 课件 PDF 页码 | 阶段 | 提交说明 / 分支 | 验证 |
| --- | --- | --- | --- |
| 2–4 | 保存实验一 | lab1-cleancode-base | 原始 16 个测试 |
| 21 | 抽取单格移动 | extract Move() | WSL 构建，16/16 通过 |
| 22 | 抽取左转 | extract TurnLeft() | WSL 构建，16/16 通过 |
| 22 | 抽取右转 | extract TurnRight() | WSL 构建，16/16 通过 |
| 24 | 封装移动命令 | extract MoveCommand | WSL 构建，16/16 通过 |
| 25 | 封装左转命令 | extract TurnLeftCommand | WSL 构建，16/16 通过 |
| 25 | 封装右转命令 | extract TurnRightCommand | WSL 构建，16/16 通过 |
| 28–32 | 继承与多态 | abstract ICommand / lab2-oop-three-features | WSL 构建，16/16 通过 |
| 35–41 | 先写 F 测试、抽取 PoseEq | feat: Add test cases for fast command | 编译成功；17 通过，FM/FL/FR 三个用例预期失败 |
| 42–44 | 实现 F 和加速状态 | test:Pass test cases for fast command / lab2-oop-support-F | WSL 构建，20/20 通过 |
| 补充 | 全方向与状态组合回归 | test: cover fast directions and state transitions | WSL 构建，38/38 通过 |

## 设计要点

- ExecutorImpl 的 Move/TurnLeft/TurnRight 将方向分支局部化。
- 嵌套 ICommand 声明纯虚 DoOperate 和虚析构函数。
- MoveCommand、TurnLeftCommand、TurnRightCommand、FastCommand 使用 public 继承与 override。
- Execute 通过 unique_ptr<ICommand> 保存具体命令，并统一调用 DoOperate。
- Fast() 切换布尔状态；IsFast() 查询状态；状态初始为 false。
- 加速 M 使用两次单格 Move()，不直接跳两格；加速 L/R 在转向前先 Move()。
- PoseEq.hpp 声明测试比较接口，PoseEq.cpp 提供唯一实现，解决多个测试文件共享的问题。

为贴近课件，本次保留其逐条创建命令对象的实现方式。Execute 的 noexcept 接口与课件一致；命令内存分配失败时遵循 noexcept 的终止语义。

## 提交记录与复现

所有提交使用执行时的真实时间，未改写历史或修改提交日期。各次重构均先编译和运行测试，再独立提交；F 测试阶段明确记录预期失败。精确哈希和时间见压缩包附带的 Git 历史及 `git log --all --date=iso-strict`。

压缩包包含完整工程、Google Test 源码、实验二课件 PDF、.git 历史、阶段验证日志与最终测试 XML；不包含机器相关的 build 目录。解压后重新构建，避免复用绝对路径相关的 CMake 缓存。详细操作见 README.md。
