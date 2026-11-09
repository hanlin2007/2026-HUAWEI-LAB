# 实验三完成说明

## 课件步骤与提交

| PDF 页码 | 内容 | 提交 |
| --- | --- | --- |
| 10–12 | 独立命令头文件 | fda69bb |
| 13–17 | PoseHandler 抽取与解耦 | ed77151 |
| 20–23 | unordered_map 表驱动 | b16ee9c |
| 26–33 | Point、Direction、模运算转向 | 37ac533 |
| 40–41 | Lambda 与 std::function | 99800ae |
| 45–46 | operator() 与生命周期安全 | 24897d4 |
| 47 | 初始化列表简化命令表 | f8ecb34 |
| 51–53 | 先编写 B/BF 测试 | 7d78949 |
| 54–56 | Point -=、倒车状态、ReverseCommand | f8253bb |
| 作业补充验证 | 完整方向矩阵与状态回归 | 39fb935 |

以上提交均在相应工作实际完成后产生，未重写历史时间。各相邻阶段之间均有实际编译、测试或检查间隔。

## 设计说明

ExecutorImpl 只负责公开接口实现和查表分发；Command 只依赖 PoseHandler，二者不再互相包含。
PoseHandler 使用 Point、指向静态 Direction 数组元素的常量指针、独立的 fast/reverse 状态。
Direction 的索引依次为 E=0、S=1、W=2、N=3，右转加一模四、左转加三模四；移动与转向直接返回静态数组元素引用。

最终命令表是静态只读的 `unordered_map<char, std::function<void(PoseHandler&)>>`，以值保存无状态函数对象，没有捕获 this 或局部变量引用。
M 在加速状态下连续调用两次单步 Move；Move 根据倒车状态调用 Forward 或 Backward，满足逐格移动要求。
L/R 在加速时先移动一格，再根据倒车状态选择相反的转向。B、F 只切换各自状态。

## 测试驱动记录

1. `7d78949` 先加入课件 4 个 B 测试和 3 个 BF 测试；实现前运行结果为 1 通过、6 失败。
2. BBM 在未实现 B 的版本上也通过，因为忽略两次 B 的结果恰好与切换两次后抵消相同。
3. `f8253bb` 实现后，原 43 项测试和新增 7 项测试全部通过。
4. 补充四方向矩阵和状态组合，以及 Point -=，最终 83 项全部通过。

日志：

- `validation/lab3/reverse-before-implementation.log`：真实失败结果。
- `validation/lab3/reverse-after-implementation.log`：实现后 50 项 CTest 结果。
- `validation/lab3/final-ctest.log`：最终 83 项 CTest 结果。
- `validation/lab3/gtest-results.xml`：最终 GTest 机器可读报告。

实际验证环境为 Ubuntu-24.04 WSL，使用工程自带 Google Test。

## 交付包

桌面压缩包包含源码、构建文件、脚本、完整 Google Test、第三次实验课件、文档、测试证据，以及完整 `.git` 历史和阶段分支。
不包含 build 缓存或本机绝对路径生成的编译产物。解压后可直接按 README 在 WSL 中重新配置构建。
