# 06 Normal Mapping

- [1. 基本动机](#1-基本动机)
- [2. 法线如何存储在纹理中](#2-法线如何存储在纹理中)
  - [编码（写入纹理）：](#编码写入纹理)
  - [解码（shader 中恢复）：](#解码shader-中恢复)
- [3. 为什么 Normal Map 看起来是紫色](#3-为什么-normal-map-看起来是紫色)
- [4. Object Space vs Tangent Space](#4-object-space-vs-tangent-space)
  - [4.1 Object Space Normal Map](#41-object-space-normal-map)
  - [4.2 Tangent Space Normal Map](#42-tangent-space-normal-map)
- [5. TBN 的构造（考试重点）](#5-tbn-的构造考试重点)
- [6. 每顶点处理](#6-每顶点处理)
- [7. 插值问题](#7-插值问题)
- [8. Fragment Shader 流程](#8-fragment-shader-流程)
- [9. 整体流程总结](#9-整体流程总结)

## 1. 基本动机

目标：
在 **不增加几何复杂度（polygon 数量）** 的情况下，增加表面细节。

核心思想：
不改变几何形状，而是**扰动参与光照计算的法线向量**。

光照模型原本为：

$$
I = f(N, L, V)
$$

Normal Mapping 后：

$$
I = f(N', L, V)
$$

其中：

* $N$：几何法线
* $N'$：来自纹理的扰动法线

几何不变，但光照结果改变 → 产生凹凸错觉。

---

## 2. 法线如何存储在纹理中

法线向量：

$$
N = (N_x, N_y, N_z)
$$

其分量范围：

$$
N_x, N_y, N_z \in [-1, 1]
$$

而普通纹理通道（RGB）范围为：

$$
[0, 1]
$$

因此必须做区间映射。

### 编码（写入纹理）：

$$
N_{stored} = \frac{N + 1}{2}
$$

### 解码（shader 中恢复）：

$$
N = 2 \cdot tex - 1
$$

这是线性映射：

$$
[-1,1] \rightarrow [0,1]
$$

原因：纹理不能存负数。

---

## 3. 为什么 Normal Map 看起来是紫色

在 Tangent Space 中，默认法线为：

$$
N_{TS} = (0,0,1)
$$

编码后：

$$
(0,0,1) \rightarrow (0.5, 0.5, 1)
$$

即：

* R = 0.5
* G = 0.5
* B = 1

蓝色分量占主导 → 呈现紫蓝色。

因为大多数表面法线接近 $(0,0,1)$，
所以大部分 normal map 都是蓝紫色。

---

## 4. Object Space vs Tangent Space

### 4.1 Object Space Normal Map

法线存储在模型坐标系中：

$$
N_{obj}
$$

特点：

* 可直接用于光照
* 不需要额外变换

缺点：

* 与模型方向绑定
* 不能复用
* 不适合动画或变形

颜色随模型方向变化明显。

---

### 4.2 Tangent Space Normal Map

为每个三角形建立局部坐标系：

* $T$：沿纹理 $u$ 方向（Tangent）
* $B$：沿纹理 $v$ 方向（Bitangent）
* $N$：几何法线

构成局部坐标系：

$$
(T, B, N)
$$

Normal map 中的法线是：

$$
N_{TS}
$$

需要通过 TBN 矩阵变换到 object space：

$$
N_{obj} = M_{TBN} \cdot N_{TS}
$$

优点：

* 与几何方向无关
* 可复用
* 支持动画
* 工业标准

---

## 5. TBN 的构造（考试重点）

已知三角形：

顶点：
$$
p_0, p_1, p_2
$$

纹理坐标：
$$
(u_0,v_0), (u_1,v_1), (u_2,v_2)
$$

定义边向量：

$$
q_1 = p_1 - p_0
$$

$$
q_2 = p_2 - p_0
$$

定义 UV 差：

$$
s_1 = u_1 - u_0, \quad t_1 = v_1 - v_0
$$

$$
s_2 = u_2 - u_0, \quad t_2 = v_2 - v_0
$$

要求：

$$
q_1 = s_1 T + t_1 B
$$

$$
q_2 = s_2 T + t_2 B
$$

矩阵形式：

$$
\begin{bmatrix}
q_1 \
q_2
\end{bmatrix}
=============

\begin{bmatrix}
s_1 & t_1 \
s_2 & t_2
\end{bmatrix}
\begin{bmatrix}
T \
B
\end{bmatrix}
$$

解得：

$$
\begin{bmatrix}
T \
B
\end{bmatrix}
=============

\frac{1}{s_1 t_2 - s_2 t_1}
\begin{bmatrix}
t_2 & -t_1 \
-s_2 & s_1
\end{bmatrix}
\begin{bmatrix}
q_1 \
q_2
\end{bmatrix}
$$

其中：

$$
s_1 t_2 - s_2 t_1
$$

是 UV 变换矩阵的行列式。

若为 0 → UV 退化 → 无法构造 TBN。

---

## 6. 每顶点处理

1. 为每个三角形计算 $T, B$
2. 归一化
3. 对共享顶点进行平均
4. 存入 vertex attribute

---

## 7. 插值问题

TBN 在 fragment shader 中是插值得到的。

插值后：

* 不再正交
* 长度不为 1

因此必须重新正交化。

常见方法（Gram-Schmidt）：

$$
T' = \text{normalize}(T - (T \cdot N)N)
$$

$$
B' = \text{cross}(N, T')
$$

保证：

* $T' \perp N$
* $B' \perp T', N$
* 三者单位长度

---

## 8. Fragment Shader 流程

每个片元：

1. 读取插值后的 TBN
2. 正交化
3. 读取 normal map
4. 解码到 $[-1,1]$
5. 变换：

$$
N_{obj} = \text{normalize}(M_{TBN} \cdot N_{TS})
$$

6. 进行光照计算

例如漫反射：

$$
L_d = k_d \max(0, N \cdot L)
$$

---

## 9. 整体流程总结

High-poly 模型
→ Bake 生成 tangent-space normal map
→ 应用于 low-poly 模型
→ 构造 TBN
→ 每片元转换法线
→ 光照计算

结果：

* 几何复杂度低
* 表面细节丰富
* 视觉效果接近高模
