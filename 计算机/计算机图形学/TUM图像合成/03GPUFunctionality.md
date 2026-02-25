# 03 GPU Functionality

## 传统图形流水线结构

* Input Assembler（IA）负责读取顶点/索引缓冲并组装图元
* Vertex Shader（VS）是 per-vertex 执行
* Primitive Assembly 在 VS 之后完成三角形组装
* Geometry Shader（GS）是 per-primitive 执行，可增删图元但性能较差
* Rasterizer 将三角形离散化为 fragments
* Fragment / Pixel Shader 负责最终像素着色
* 管线是固定阶段串行结构（stage-based, rigid）

---

## Tessellation 阶段

为了支持细分曲面，增加了 Tessellation Control Shader（TCS）和 Tessellation Evaluation Shader（TES）两个阶段：

* Tessellation Control Shader（TCS）决定细分因子，决定细分程度
* 固定功能 Tessellator 生成新顶点
* Tessellation Evaluation Shader（TES）计算新顶点位置
* 属于传统固定管线扩展
* 仍然受限于阶段化结构

管线结构（加入 Tessellation）

顺序变为：

* Input Assembler
* Vertex Shader
* Tessellation Control Shader (TCS)
* Tessellator（固定功能单元）
* Tessellation Evaluation Shader (TES)
* Geometry Shader（可选）
* Rasterization
* Fragment Shader (Pixel Shader)

---

## 传统管线的局限

* 剔除通常过晚（VS 之后）
* GS 性能不理想
* CPU 需要大量 draw call
* 无法高效处理超大规模动态几何
* 数据流模式限制跨阶段优化

---

## Mesh Shading Pipeline

* 用 Task Shader + Mesh Shader 替代 VS/GS/Tess
* 几何处理转为 task-based 模型
* 以 workgroup 为基本执行单位
* 更接近 compute shader 执行方式
* 支持 GPU 端细粒度剔除与 LOD

---

## Task Shader 关键点

* 可选阶段
* 以 workgroup 执行
* 负责几何调度（amplification）
* 可执行 frustum culling
* 可选择 LOD
* 可 spawn 0~n 个 Mesh Shader workgroups
* 可传递 payload 给 Mesh Shader

---

## Mesh Shader 关键点

* 以 workgroup 执行
* 负责生成顶点与图元
* 显式输出 vertex 数组与 primitive 索引
* 每个 workgroup 输出数量有硬件上限
* 替代传统 IA + VS + GS
* 几何阶段 compute 化

---

## Meshlet 概念

* 将大型模型拆分为小块（meshlet）
* 每个 meshlet 匹配一个 workgroup 粒度
* 每个 meshlet 有局部顶点和索引
* GPU 端可做 meshlet 级别剔除
* 支持动态 LOD
* 减少 CPU draw call

---

## Compute Shader 执行模型

* 无图元概念
* 使用 Dispatch 启动线程
* 三层结构：

  * Dispatch Grid
  * Thread Group
  * Thread
* 通过 `[numthreads(x,y,z)]` 定义 group 内线程数
* `SV_DispatchThreadID` 提供全局线程 ID
* 线程组内部可共享共享内存

---

## SIMD / SIMT 概念

* SIMD：Single Instruction Multiple Data
* 同一指令作用于多数据
* GPU 实际为 SIMT（Single Instruction Multiple Threads）
* 适合大规模数据并行问题

---

## 卷积实现关键点

* 每线程处理一个像素
* 邻域遍历实现卷积
* 使用 clamp 处理边界
* 数学形式：
  $$
  I'(x,y)=\sum I(x+i,y+j)w(i,j)
  $$
* 可使用 shared memory 优化

---

## OptiX 执行模型

* 光线为基本处理单位
* 使用 BVH 加速结构
* 利用 RT Core 加速相交测试
* 用户只编写 ray 行为程序
* 框架负责遍历与调度

---

## OptiX 程序类型

* Ray Generation Program：生成主光线
* Intersection Program：自定义几何相交
* Any Hit Program：遍历阶段过滤器
* Closest Hit Program：最近交点着色
* Miss Program：无交点处理
* Exception Program：异常处理

---

## Hit 概念

* Hit = 光线与几何体相交
* 光线可能有多个交点
* 定义：
  $$
  r(t)=o+t d
  $$
* 交点对应某个 $t>0$

---

## Closest Hit

* 对最近有效交点执行
* 最近定义为最小 $t$
* 只执行一次
* 负责材质计算
* 可发射次级光线
* 等价于光栅化中的 Fragment Shader

---

## Any Hit

* 每遇到交点可能执行
* 不保证顺序
* 可忽略交点（ignore）
* 可提前终止光线（terminate）
* 用于透明测试与 shadow ray
* 不负责最终着色

---

## Shadow Ray 机制

* 目标：判断是否存在遮挡
* 不关心最近交点
* 任意不透明交点即可终止
* 使用 Any Hit 提前结束遍历

---

## Shader Binding Table（SBT）

* 映射：
  Ray Type × Geometry Instance → Shader
* 绑定：

  * 哪个 Closest Hit
  * 哪个 Any Hit
  * 材质数据
* 作用：决定“用哪个程序计算”
* 不决定数学公式，只决定程序选择

---

## 重心坐标插值

* 三角形内一点：
  $$
  P=\alpha A+\beta B+\gamma C
  $$
* 满足：
  $$
  \alpha+\beta+\gamma=1
  $$
* UV 插值：
  $$
  uv=\alpha uv_A+\beta uv_B+\gamma uv_C
  $$
* 等价于光栅化属性插值

---

## Ray Generation 流程

* 每像素生成一条主光线
* 初始化 payload
* 调用 `optixTrace()`
* trace 结束后写入输出缓冲

---

## optixTrace 内部逻辑

* BVH traversal
* 相交测试
* 调用 Any Hit（可选）
* 维护最近交点
* 调用 Closest Hit 或 Miss
* 返回 RayGen

---

## 多交点记录机制

* 在 Any Hit 中记录所有交点
* 顺序不保证
* 需按 $t$ 排序
* 可用于透明叠加与体渲染

---

## Rasterization 与 Ray Tracing 对比

光栅化：

* 三角形 → 像素

光线追踪：

* 光线 → 三角形

控制方向完全相反。

---

