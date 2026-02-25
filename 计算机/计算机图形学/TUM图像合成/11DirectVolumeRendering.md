# 11 Direct Volume Rendering

- [1. 动机](#1-动机)
- [2. 数据表示](#2-数据表示)
- [3. 光学模型（Optical Model）](#3-光学模型optical-model)
  - [3.1 基本物理过程](#31-基本物理过程)
- [4. Radiative Transfer Equation (RTE)](#4-radiative-transfer-equation-rte)
- [5. 透射率与光学深度](#5-透射率与光学深度)
- [6. Volume Rendering Integral（发射+吸收）](#6-volume-rendering-integral发射吸收)
- [7. 离散化](#7-离散化)
- [8. Front-to-Back Compositing](#8-front-to-back-compositing)
- [9. 散射模型](#9-散射模型)
- [10. 常见光学简化](#10-常见光学简化)
- [11. 加速技术](#11-加速技术)
  - [11.1 Empty Space Skipping](#111-empty-space-skipping)
  - [11.2 Early Ray Termination](#112-early-ray-termination)
- [12. 核心理解总结](#12-核心理解总结)
- [考试版本](#考试版本)
  - [一、从 RTE 到 Volume Rendering Integral](#一从-rte-到-volume-rendering-integral)
    - [1. 方向导数形式（RTE）](#1-方向导数形式rte)
    - [2. 光学深度（Optical Depth）](#2-光学深度optical-depth)
    - [3. 解微分方程（关键推导）](#3-解微分方程关键推导)
      - [物理解释](#物理解释)
  - [二、离散化 → Alpha Compositing](#二离散化--alpha-compositing)
    - [4. 离散采样](#4-离散采样)
    - [5. 离散积分形式](#5-离散积分形式)
    - [6. 转换为递推（Front-to-Back）](#6-转换为递推front-to-back)
      - [关键等价关系](#关键等价关系)
  - [三、散射模型（考试可能问）](#三散射模型考试可能问)
  - [四、考试高频问法总结](#四考试高频问法总结)
  - [五、一句话本质总结](#五一句话本质总结)

## 1. 动机

体渲染用于表示：

- 爆炸
- 烟雾
- 云
- 大气现象
- 医学CT/MRI数据

特点：

- 无明确几何边界
- 内部参与介质（participating media）
- 光在体内发生吸收、散射、发射



## 2. 数据表示

体数据存储在规则3D网格（regular grid）上：

- 数据值存储在网格顶点
- 相邻8个顶点构成一个cell
- 使用trilinear interpolation重建连续场

射线参数化：

$$
x(s) = x_0 + s\omega
$$



## 3. 光学模型（Optical Model）

### 3.1 基本物理过程

1. Emission（发射）
2. Absorption（吸收）
3. Out-scattering（散射离开）
4. In-scattering（散射进入）

吸收系数：

$$
\sigma_a(x)
$$

散射系数：

$$
\sigma_s(x)
$$

总消光系数：

$$
\sigma_t(x) = \sigma_a(x) + \sigma_s(x)
$$



## 4. Radiative Transfer Equation (RTE)

方向导数形式：

$$
(\omega \cdot \nabla)L(x,\omega)
= \text{emission} - \sigma_t L
+
\text{in-scattering}
$$

若只考虑吸收：

$$
\frac{dL}{ds} = -\sigma_a L
$$


## 5. 透射率与光学深度

光学深度：

$$
\tau(s_1,s_2) = \int_{s_1}^{s_2} \sigma_t(s)\,ds
$$

透射率：

$$
T(s_1,s_2) = e^{-\tau(s_1,s_2)}
$$

Beer's Law：

$$
L(D) = L(s_0)e^{-\tau(s_0,D)}
$$



## 6. Volume Rendering Integral（发射+吸收）

完整积分形式：

$$
L(D,\omega)
=
L(s_0,\omega)e^{-\tau(s_0,D)}
+
\int_{s_0}^{D}
L_e(s,\omega)
e^{-\tau(s,D)} ds
$$

物理意义：

- 第一项：背景光衰减
- 第二项：沿途发射贡献（带前向透射率）



## 7. 离散化

等步长采样：

$$
\tau_i = \sigma_t(s_i)\Delta s
$$

透射率近似：

$$
T_i \approx 1 - \tau_i
$$

离散求和形式：

$$
I_D
=
\sum_{i=0}^{n}
c_i (1 - T_i)
\prod_{j=i+1}^{n} T_j
$$

其中：

- $c_i \approx L_e(s_i)$
- $T_i$ = transparency
- $\alpha_i = 1 - T_i$ = opacity



## 8. Front-to-Back Compositing

初始化：

$$
C_{in}=0,\quad \alpha_{in}=0
$$

递推公式：

$$
C_{out}
=
C_{in}
+
(1-\alpha_{in})\alpha C
$$

$$
\alpha_{out}
=
\alpha_{in}
+
(1-\alpha_{in})\alpha
$$

含义：

- $(1-\alpha_{in})$ = 当前剩余透射率
- 来源于连续模型中的 $\prod T_j$

注意：

- 按视线方向 front-to-back 累积
- “in”表示已累积结果，不是光源



## 9. 散射模型

各向同性：

$$
f_p = \frac{1}{4\pi}
$$

Henyey–Greenstein模型：

$$
f_p(\phi)
=
\frac{1}{4\pi}
\frac{1-g^2}{(1+g^2-2g\cos\phi)^{3/2}}
$$

参数：

- $g=0$：各向同性
- $g>0$：前向散射
- $g<0$：后向散射

Rayleigh scattering：

$$
\propto \frac{1}{\lambda^4}
$$



## 10. 常见光学简化

1. Absorption only
2. Emission only
3. Absorption + Emission（最常用）
4. Single Scattering
5. Multiple Scattering



## 11. 加速技术

### 11.1 Empty Space Skipping

- 使用max-pyramid
- 跳过低opacity区域

### 11.2 Early Ray Termination

当：

$$
\alpha_{in} \approx 1
$$

停止采样。



## 12. 核心理解总结

体渲染本质：

1. 解一维常微分方程
2. 得到指数衰减积分
3. 离散化为透明度递推
4. 用front-to-back compositing实现

关键物理特征：

- 指数衰减
- 透射率乘积
- 非线性叠加

## 考试版本

### 一、从 RTE 到 Volume Rendering Integral

#### 1. 方向导数形式（RTE）

沿方向 ω：

$$(\omega \cdot \nabla)L(x,\omega)
= L_e(x,\omega) - \sigma_t(x)L(x,\omega) + \text{in-scattering}$$

若只考虑 Emission + Absorption：

$$ \frac{dL}{ds}
= L_e(s)
- \sigma_t(s)L(s)
$$

这是一个一阶线性常微分方程。



#### 2. 光学深度（Optical Depth）

$$
\tau(s_1,s_2)
=
\int_{s_1}^{s_2}
\sigma_t(s)\,ds
$$

透射率：

$$
T(s_1,s_2)
=
e^{-\tau(s_1,s_2)}
$$



#### 3. 解微分方程（关键推导）

标准解形式：

$$
L(D)
=
L(s_0) e^{-\tau(s_0,D)}
+
\int_{s_0}^{D}
L_e(s)
e^{-\tau(s,D)} ds
$$



##### 物理解释

1️⃣ 第一项：背景光指数衰减  
2️⃣ 第二项：沿途发射 × 前向透射率  

核心特征：

$$
\text{指数衰减权重}
$$



### 二、离散化 → Alpha Compositing



#### 4. 离散采样

等步长 Δs：

$$
\tau_i = \sigma_t(s_i)\Delta s
$$

近似：

$$
T_i \approx 1 - \tau_i
$$



#### 5. 离散积分形式

$$
I
=
\sum_{i=0}^{n}
c_i (1-T_i)
\prod_{j=i+1}^{n} T_j
$$

其中：

- $c_i \approx L_e(s_i)$
- $T_i$ = transparency
- $\alpha_i = 1-T_i$



#### 6. 转换为递推（Front-to-Back）

初始化：

$$
C_{in}=0,\quad \alpha_{in}=0
$$

递推：

$$
C_{out}
=
C_{in}
+
(1-\alpha_{in})\alpha C
$$

$$
\alpha_{out}
=
\alpha_{in}
+
(1-\alpha_{in})\alpha
$$



##### 关键等价关系

$$
\prod T_j
\quad \Longleftrightarrow \quad
(1-\alpha_{in})
$$

Front-to-Back 是连续透射率乘积的递推实现。



### 三、散射模型（考试可能问）

各向同性：

$$
f_p = \frac{1}{4\pi}
$$

Henyey-Greenstein：

$$
f_p(\phi)
=
\frac{1}{4\pi}
\frac{1-g^2}
{(1+g^2-2g\cos\phi)^{3/2}}
$$

参数：

- $g=0$ → 各向同性
- $g>0$ → 前向散射
- $g<0$ → 后向散射



### 四、考试高频问法总结

1. 写出 Volume Rendering Integral
2. 解释光学深度与透射率
3. 推导离散形式
4. 解释为什么是指数衰减
5. 说明 front-to-back 与 $\prod T_j$ 的关系
6. 区分 absorption / emission / scattering
7. 单次 vs 多次散射区别



### 五、一句话本质总结

体渲染 =

$$
\text{解一维光传输微分方程}
\rightarrow
\text{指数衰减积分}
\rightarrow
\text{透明度递推合成}
$$