# trajectory_reconstructor
纯相对感知结果重构相对路径进行跟踪

## 算法框架逻辑结构

项目已提供最小可扩展的算法框架，按以下阶段组织：

1. `ObservationPreprocessor`：预处理/过滤相对感知结果  
2. `PathReconstructor`：将预处理结果重构为路径  
3. `TrajectoryTracker`：基于重构路径输出跟踪结果  

统一入口为 `TrajectoryFramework.run()`，负责按固定顺序串联以上三个阶段。
