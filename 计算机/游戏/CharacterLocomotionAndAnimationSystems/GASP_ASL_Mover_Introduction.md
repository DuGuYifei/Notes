# GASP ASL Mover Introduction

【GASP（角色运动结构方法论）】

G — Gesture（动作意图 / 整体姿态）
- 定义角色“想做什么”
- 强调整体轮廓与方向感
- 姿态一眼可读（Silhouette）
- 先大形体，后细节
- 决定动作的情绪与性格

A — Anticipation（预备动作）
- 主动作发生前的准备
- 通常与主运动方向相反
- 提高动作可读性与真实感
- 起步、转向、攻击前摇
- 没有 anticipation 会显得突兀

S — Spacing（时间与位移分配）
- 控制速度、重量、力度
- 间距大 = 快
- 间距小 = 慢
- 非均匀 spacing 更自然
- 影响加速、减速、停顿

P — Path（运动轨迹）
- 肢体与 Root 的运动路线
- 生物运动以弧线为主
- 避免僵硬直线
- 路径断裂会显得机械
- 影响流畅度与稳定性

GASP 核心
- 关注“怎么动”
- 偏运动逻辑与物理合理性
- 适合游戏与系统驱动动画


【ASL（动画表现原则）】

A — Anticipation（表演性预备）
- 强调视觉提示
- 包含表情、眼神、姿态变化
- 可夸张以增强表现
- 提升观众理解速度

S — Squash & Stretch（挤压与拉伸）
- 表现重量、弹性、生命感
- 体积守恒
- 落地、加速、停顿时明显
- 写实动画中为微形变
- 卡通动画中可大幅使用

L — Line of Action（动作线）
- 姿态的主方向线
- 全身一条核心力量线
- 避免直立、对称、僵硬
- 强化动作张力与节奏
- 与 Gesture 强相关

ASL 核心
- 关注“好不好看”
- 偏表演与生命力
- 多用于 Cinematic 与 Stylized 动画


【Mover（Unreal Engine 角色移动系统）】

定位
- 运行时角色移动系统
- 替代传统 CharacterMovementComponent
- 以运动逻辑为核心
- 动画作为表现层

核心概念
- Movement Intent（移动意图）
- Desired Velocity
- Movement Mode（走 / 跑 / 跳 / 冲刺）
- Trajectory Prediction
- Network Prediction

与 GASP 的对应
- Gesture → 输入意图 / 目标速度
- Anticipation → 加速缓冲 / 状态预测
- Spacing → 加速度 / 减速度 / 摩擦
- Path → Root Motion 轨迹 / Motion Warping

系统特性
- 禁止瞬时速度变化
- 强制惯性与重量感
- 支持 Root Motion 与 In-Place
- 适配动画混合与网络同步
- 强约束动画位移正确性

动画制作要求
- 起步与停步需匹配加速度
- Root Motion 路径必须干净
- 避免用动画强行拉位移
- 动画需可被打断与混合

Mover 核心
- 强工程约束
- 偏 GASP 思维
- 服务于 Gameplay 与系统稳定性
