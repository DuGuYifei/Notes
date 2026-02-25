# 05 Transparency Rendering


## 1. 问题定义

透明渲染的核心区别：

1. 一个 pixel 可能对应多个 fragment
2. Z-buffer 只保留最近的 fragment
3. Alpha blending 是非交换的（顺序影响结果）

Alpha 混合公式：

$$
C = α_src C_src + (1 - α_src) C_dest
$$


由于：
$$
α_f C_f + (1 - α_f) α_b C_b
≠
α_b C_b + (1 - α_b) α_f C_f
$$

因此：

透明渲染必须按照正确的深度顺序混合。

关键矛盾：

* 正确顺序是 pixel 级
* 传统排序是 object 级

---

## 2. 传统方法：Back-to-Front 排序

流程：

1. 先渲染不透明物体

   * 开启 depth test
   * 写入 depth buffer

2. 对透明物体按从远到近排序

3. 渲染透明物体

   * 开启 depth test（不写 depth）
   * 开启 alpha blending

优点：

* 简单
* 只需一次透明渲染

缺点：

* 每帧都要排序
* 物体相互穿插时排序失败
* 本质仍是 object 级排序

---

## 3. Depth Peeling

### 目标

在不排序物体的情况下，获得每个 pixel 的所有深度层。

### 核心思想

多次渲染场景，每次剥离一层。

第 i 次 pass：

丢弃所有：
$$
z ≤ z_{i-1}
$$

再使用标准 depth test 得到第 i 层。

最终得到：

$$
z₁, z₂, z₃, …, z_{d_c}
$$

其中：

d_c = depth complexity
= 单个 pixel 上的最大 fragment 数

### 代价

Pass 数：

$$
Passes = d_c
$$

总成本：

$$≈ d_c × 透明几何渲染成本$$

---

## 4. Depth Complexity 的计算

步骤：

1. 关闭 depth test
2. 每生成一个 fragment，stencil++
3. 得到每个 pixel 的 fragment 数

然后做并行 reduction：
$$
n×n → n/2×n/2 → … → 1×1
$$
需要：

log₂(n) 次 pass

最终得到最大 depth complexity。

---

## 5. Per-Pixel Linked List（Order Independent Transparency）

依赖：

* UAV（可读写 buffer）
* Atomic 操作

目标：

一次渲染收集所有 fragment，
在 pixel 内部排序。

---

## 6. 数据结构

### Fragment & Link Buffer

struct Node {
float depth;
float4 color;
int next;
}

* 存储所有 fragment
* 需要全局 atomic counter

### Start Offset Buffer

* 尺寸 = 屏幕分辨率
* 每个 pixel 存链表头指针
* 初始值 = -1

-1 表示空链表。

---

## 7. 收集阶段（Collection Phase）

对每个透明 fragment：

index = atomicCounter++
oldHead = StartOffset[x,y]
Node[index].next = oldHead
StartOffset[x,y] = index

特点：

* 头插法
* O(1) 插入
* 不排序
* 不做 blending
* 仅收集所有 fragment

链表顺序与 z 无关，只与插入顺序有关。

---

## 8. 解析阶段（Resolve Phase）

渲染 fullscreen quad。

对每个 pixel：

1. head = StartOffset[x,y]
2. 遍历链表，收集所有 fragment
3. 按深度排序（远 → 近）
4. 执行 alpha blending

得到最终颜色。

---

## 9. 方法对比

Back-to-front 排序

* 几何遍历：1 次
* 是否 pixel 级排序：否
* 内存开销：低
* 不需要 atomic

Depth Peeling

* 几何遍历：d_c 次
* 是否 pixel 级排序：是
* 内存开销：低
* 不需要 atomic

Per-pixel linked list

* 几何遍历：1 次
* 是否 pixel 级排序：是
* 内存开销：高
* 需要 atomic

---

## 10. 核心结论

1. 透明渲染本质是 pixel 级排序问题。
2. Z-buffer 只能解决最近层。
3. Depth peeling 用多 pass 换正确性。
4. Per-pixel linked list 用内存与同步换单次几何遍历。
5. 本质权衡是：

多次渲染  vs  内存 + 原子操作开销。
