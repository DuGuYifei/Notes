# 09 Radiosity

- [1. 基本思想](#1-基本思想)
  - [1.1 起源与假设](#11-起源与假设)
- [2. 平均 Radiosity 定义](#2-平均-radiosity-定义)
- [3. Form Factor（几何能量传输）](#3-form-factor几何能量传输)
  - [3.1 定义](#31-定义)
  - [3.2 各项解释](#32-各项解释)
  - [3.3 物理意义](#33-物理意义)
  - [3.4 重要性质](#34-重要性质)
    - [(1) 自身 form factor](#1-自身-form-factor)
    - [(2) 能量守恒](#2-能量守恒)
    - [(3) Reciprocity](#3-reciprocity)
- [4. 经典 Radiosity 方程](#4-经典-radiosity-方程)
- [5. 矩阵形式](#5-矩阵形式)
- [6. 矩阵性质](#6-矩阵性质)
- [7. Form Factor 计算方法](#7-form-factor-计算方法)
  - [7.1 Hemicube 方法](#71-hemicube-方法)
- [8. 直接解法](#8-直接解法)
- [9. 迭代方法](#9-迭代方法)
  - [9.1 Neumann 展开](#91-neumann-展开)
  - [9.2 Jacobi（Gathering）](#92-jacobigathering)
  - [9.3 Gauss–Seidel](#93-gaussseidel)
  - [9.4 Shooting（Progressive Refinement）](#94-shootingprogressive-refinement)
- [10. 渲染结果](#10-渲染结果)
- [11. Ambient Correction](#11-ambient-correction)
- [12. Radiosity vs Ray Tracing](#12-radiosity-vs-ray-tracing)
- [13. Radiosity vs Photon Mapping](#13-radiosity-vs-photon-mapping)
- [14. 本质总结](#14-本质总结)


## 1. 基本思想

### 1.1 起源与假设

* 起源：热辐射模拟
* 场景被划分为有限个平面 patch（finite elements）
* 所有表面假设为 **Lambertian（理想漫反射）**

Lambertian BRDF：

$$
f_r = \frac{\rho}{\pi}
$$

性质：

* 与方向无关
* 出射辐射在所有方向一致
* 每个 patch 只需一个标量 $B_i$

---

## 2. 平均 Radiosity 定义

对 patch $A_i$：

$$
B_i = \frac{1}{A_i}\int_{A_i} B(x), dA
$$

意义：

* 将连续函数 $B(x)$ 离散为 patch 常数
* 这是有限元离散步骤
* 此时还没有 form factor

---

## 3. Form Factor（几何能量传输）

### 3.1 定义

$$
F_{ij} =
\frac{1}{A_i}
\int_{x\in A_i}
\int_{y\in A_j}
\frac{V(x,y)\cos\theta_x \cos\theta_y}
{\pi |x-y|^2}
, dA_y dA_x
$$

---

### 3.2 各项解释

* $V(x,y)$：可见性函数（0 或 1）
* $\cos\theta_x$：出射角余弦
* $\cos\theta_y$：入射角余弦
* $|x-y|^2$：距离平方衰减
* $\frac{1}{\pi}$：来自 Lambert BRDF
* $\frac{1}{A_i}$：对 patch $i$ 取平均

---

### 3.3 物理意义

$$
F_{ij}
$$

表示：

> 从 patch $j$ 发出的能量中，有多少比例到达 patch $i$

特点：

* 仅与几何相关
* 与材质、光源无关

---

### 3.4 重要性质

#### (1) 自身 form factor

$$
F_{ii} = 0
$$

---

#### (2) 能量守恒

$$
\sum_{j=1}^{N} F_{ij} \le 1
$$

---

#### (3) Reciprocity

$$
A_i F_{ij} = A_j F_{ji}
$$

---

## 4. 经典 Radiosity 方程

$$
B_i = E_i + \rho_i \sum_{j=1}^{N} B_j F_{ij}
$$

含义：

* 出射能量
* 等于自发光
* 加上反射的入射能量

---

## 5. 矩阵形式

定义：

$$
T_{ij} = \rho_i F_{ij}
$$

则：

$$
B = E + T B
$$

移项：

$$
(I - T)B = E
$$

---

## 6. 矩阵性质

* 未知数：$n$（patch 数量）
* form factor 数量：$n^2$
* 直接求解复杂度：$O(n^3)$

对于平面 patch：

$$
F_{ii} = 0
$$

矩阵为对角占优（diagonal dominant）：

$$
|a_{ii}| > \sum_{j \ne i} |a_{ij}|
$$

保证迭代法收敛。

---

## 7. Form Factor 计算方法

### 7.1 Hemicube 方法

思想：

* 用 hemicube 代替 hemisphere
* 将其离散为小格
* 每格预计算 $\Delta F$

计算：

$$
F_{ij} = \sum_{q \in A_j} \Delta F_q
$$

步骤：

1. patch $i$ 中心设为视点
2. 渲染 hemicube 五个面
3. 用 patch ID 着色
4. depth buffer 做可见性
5. 累加对应 $\Delta F$

---

## 8. 直接解法

$$
B = (I-T)^{-1}E
$$

复杂度：

$$
O(n^3)
$$

通常不可行。

---

## 9. 迭代方法

### 9.1 Neumann 展开

$$
B = E + TE + T^2E + T^3E + \dots
$$

物理意义：

* 0 次反射
* 1 次反射
* 2 次反射
* …

---

### 9.2 Jacobi（Gathering）

$$
B_i^{(k+1)} =
E_i + \rho_i \sum_{j=1}^{N} B_j^{(k)} F_{ij}
$$

特点：

* 使用上一轮全部值
* 并行友好
* 收敛慢

---

### 9.3 Gauss–Seidel

更新时使用最新值：

$$
B_i^{(k+1)} =
E_i + \rho_i
\left(
\sum_{j<i} B_j^{(k+1)} F_{ij}
+
\sum_{j>i} B_j^{(k)} F_{ij}
\right)
$$

特点：

* 收敛更快
* 不易并行

---

### 9.4 Shooting（Progressive Refinement）

初始化：

$$
B = \Delta B = E
$$

循环：

选最大 $\Delta B_i$，更新：

$$
B_j \leftarrow B_j + \rho_j \Delta B_i F_{ji}
$$

$$
\Delta B_j \leftarrow \Delta B_j + \rho_j \Delta B_i F_{ji}
$$

然后：

$$
\Delta B_i = 0
$$

特点：

* importance driven
* 收敛快
* 早期结果合理

---

## 10. 渲染结果

求解得到：

* 每 patch 常数 $B_i$
* 与视点无关

渲染方式：

* 直接绘制 patch
* Gouraud 插值
* 生成 radiosity texture

---

## 11. Ambient Correction

为避免 progressive refinement 早期过暗：

$$
B_{display} = B + B_{ambient}
$$

其中：

$$
B_{ambient} \propto \sum_i \Delta B_i
$$

随收敛逐渐消失。

---

## 12. Radiosity vs Ray Tracing

| 属性         | Ray Tracing | Radiosity |
| ---------- | ----------- | --------- |
| Specular   | 支持          | 不支持       |
| Diffuse GI | 成本高         | 原生支持      |
| 视点依赖       | 是           | 否         |
| 噪声         | 有           | 无         |

---

## 13. Radiosity vs Photon Mapping

Photon Mapping：

* 随机采样
* 支持任意 BRDF
* 有方差

Radiosity：

* 确定性
* 平滑
* 仅支持漫反射

---

## 14. 本质总结

Radiosity 是：

* 将 rendering equation 在 Lambertian 假设下离散化
* 得到线性能量守恒系统
* 数值求解多次漫反射

核心公式：

$$
B_i = E_i + \rho_i \sum_j B_j F_{ij}
$$

这就是整个 Lecture 08 的数学核心。
