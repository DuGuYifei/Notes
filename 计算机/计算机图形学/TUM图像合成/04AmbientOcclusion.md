# 04 Ambient Occlusion

- [Ambient Occlusion（AO）理论基础](#ambient-occlusionao理论基础)
  - [理论定义](#理论定义)
  - [与渲染方程的关系](#与渲染方程的关系)
  - [Monte Carlo 近似](#monte-carlo-近似)
- [AO 的三种实现方式](#ao-的三种实现方式)
  - [1. Raytracing AO](#1-raytracing-ao)
  - [2. Object Space AO](#2-object-space-ao)
  - [3. Screen Space AO（SSAO）](#3-screen-space-aossao)
- [SSAO 核心算法](#ssao-核心算法)
  - [1. 重建 view-space 位置](#1-重建-view-space-位置)
  - [2. 构造采样点](#2-构造采样点)
  - [3. 投影并读取深度](#3-投影并读取深度)
  - [4. 深度比较](#4-深度比较)
- [SSAO 的关键几何点](#ssao-的关键几何点)
- [SSAO + Normal Buffer](#ssao--normal-buffer)
- [随机化（防止 Banding）](#随机化防止-banding)
- [Gaussian Blur](#gaussian-blur)
- [Bilateral Filter](#bilateral-filter)
- [SSAO 完整 Pipeline](#ssao-完整-pipeline)
- [关键参数](#关键参数)
- [核心理解总结](#核心理解总结)


## Ambient Occlusion（AO）理论基础

### 理论定义

AO 定义为法线半球上的可见性加权积分：

$$
k_a(p)=\frac{1}{\pi}\int_{\Omega^+} V(\omega)\cos\theta \, d\omega
$$

其中：

- $\Omega^+$：以法线为轴的上半球
- $V(\omega)$：可见性函数（无遮挡=1，被遮挡=0）
- $\theta$：入射方向与法线夹角
- $\cos\theta = n \cdot \omega$

归一化来源：

$$
\int_{\Omega^+} \cos\theta \, d\omega = \pi
$$

因此无遮挡时 $k_a=1$。

---

### 与渲染方程的关系

从 Lambert 漫反射模型：

$$
L_o = \frac{\rho_d}{\pi} \int_{\Omega^+} L_i \cos\theta \, d\omega
$$

若假设：

- 环境光各向同性常数 $L_i=L_{env}$
- 仅可见方向贡献 $L_i=L_{env}V(\omega)$

则：

$$
L_o = \rho_d L_{env}
\left(
\frac{1}{\pi}\int_{\Omega^+} V(\omega)\cos\theta d\omega
\right)
$$

括号内即 AO。

AO 本质：环境 irradiance 的几何可见性部分。

---

### Monte Carlo 近似

若均匀半球采样：

$$
k_a \approx \frac{2}{n}\sum V(\omega_i)\cos\theta_i
$$

若采用 cos-weighted 采样：

$$
k_a \approx \frac{1}{n}\sum V(\omega_i)
$$

工程实现常直接使用“可见样本比例”。

---

## AO 的三种实现方式

### 1. Raytracing AO

- 在世界空间发射半球射线
- 显式计算 $V(\omega)$
- 精度高，成本高
- 常用于离线预计算

---

### 2. Object Space AO

- 在物体空间近似几何遮挡
- 不真实射线求交
- 多用于静态模型

---

### 3. Screen Space AO（SSAO）

- 在图像空间近似 $V(\omega)$
- 输入：depth buffer（+normal buffer）
- 实时渲染主流方法

---

## SSAO 核心算法

### 1. 重建 view-space 位置

从屏幕坐标与线性深度恢复：

$$
p_v = (x_p,y_p,z_p)
$$

---

### 2. 构造采样点

$$
q_i = p_v + r_i d_i
$$

理论深度：

$$
q_i^d = z_p + r_i d_{iz}
$$

---

### 3. 投影并读取深度

将 $q_i$ 投影回屏幕，读取：

$$
d_{q_i}
$$

---

### 4. 深度比较

若：

$$
d_{q_i} < q_i^d
$$

则发生遮挡。

AO 估计：

$$
k_a = 1 - \frac{1}{n}\sum (q_i^d > d_{q_i} ? 1:0)
$$

---

## SSAO 的关键几何点

- 半径 $R$ 定义在 view space
- 屏幕半径 $\propto R/z$
- 必须使用 linear depth
- 比较的是“样本理论深度”与“真实深度”

---

## SSAO + Normal Buffer

增加约束：

$$
d_i \cdot n_p > 0
$$

仅采样法线正半球。

更接近理论 $\Omega^+$。

$$
k_a(p) =
1 - \frac{1}{n}
\sum_{i=1}^{n}
\left(
(q_i^d > d_{q_i} \; ? \; 1 : 0)
\;
(d_i \cdot n > 0 \; ? \; 1 : 0)
\right)
$$

---

## 随机化（防止 Banding）

规则采样 → 条纹伪影  
随机采样 → 噪声

方法：

- 每像素随机旋转采样核
- 半径抖动
- noise texture

---

## Gaussian Blur

二维高斯核：

$$
G(x,y)=\frac{1}{2\pi\sigma^2}
\exp\left(-\frac{x^2+y^2}{2\sigma^2}\right)
$$

卷积：

$$
AO'(u,v)=\sum AO(u+i,v+j)G(i,j)
$$

Gaussian 可分离：

$$
G(x,y)=G_x(x)G_y(y)
$$

计算复杂度从 $n^2$ 降至 $2n$。

---

## Bilateral Filter

为避免 halo：

$$
w = G_s(||p-q||)\cdot G_r(|z_p-z_q|)
$$

深度差大 → 权重小 → 保持边缘。

---

## SSAO 完整 Pipeline

1. 渲染场景，输出 depth + normal
2. 重建 view-space 位置
3. 半球采样 + 深度比较
4. 随机化
5. Gaussian / Bilateral blur
6. 与原图相乘

---

## 关键参数

- radius：遮挡尺度
- directions / steps：采样精度
- angle bias：避免 self-occlusion
- spatial sigma：模糊强度
- range sigma：深度敏感度

---

## 核心理解总结

AO 本质：

$$
\text{环境 irradiance 的几何可见性积分}
$$

SSAO 本质：

$$
\text{在屏幕空间近似 } V(\omega)
$$

工程核心思想：

少量采样 + 随机化 + 边缘感知滤波。