# 07 Global Illumination

- [1. Lighting Models](#1-lighting-models)
  - [Local Illumination](#local-illumination)
  - [Global Illumination (GI)](#global-illumination-gi)
- [2. Radiative Transfer](#2-radiative-transfer)
- [3. Radiometric Quantities](#3-radiometric-quantities)
  - [3.1 Radiant Energy](#31-radiant-energy)
  - [3.2 Radiant Power](#32-radiant-power)
  - [3.3 Irradiance](#33-irradiance)
  - [3.4 Radiant Intensity](#34-radiant-intensity)
  - [3.5 Solid Angle](#35-solid-angle)
- [4. Radiance（核心物理量）](#4-radiance核心物理量)
- [5. Radiance 与 Irradiance 关系](#5-radiance-与-irradiance-关系)
- [6. BRDF](#6-brdf)
  - [BRDF 性质](#brdf-性质)
- [7. Reflectance Equation](#7-reflectance-equation)
- [8. Rendering Equation](#8-rendering-equation)


## 1. Lighting Models

### Local Illumination

只考虑 direct light，不考虑场景中其他物体。

$$
L_o(x,\omega_o) = f_r(x,\omega_i,\omega_o)\, L_i(x,\omega_i)\cos\theta_i
$$

特点：

- 无 shadow
- 无 indirect light
- 无 multiple bounce
- 每个点独立计算

---

### Global Illumination (GI)

考虑 light 与整个 scene 的相互作用：

- indirect light
- shadow
- multiple reflection
- transmission
- volumetric scattering

必须使用积分形式（Rendering Equation）。

---

## 2. Radiative Transfer

描述光因以下机制发生变化：

- Emission
- Absorption
- Scattering

采用 Geometric Optics 假设：

- 光沿直线传播
- 光线之间互不干扰
- 仅在 light–matter interaction 时改变方向

适用条件：

$$
\text{geometry size} \gg \lambda
$$

---

## 3. Radiometric Quantities

### 3.1 Radiant Energy

$$
Q \quad [J]
$$

总能量。

---

### 3.2 Radiant Power

$$
\Phi = \frac{dQ}{dt}
$$

单位：$W = J/s$

单位时间的能量。

---

### 3.3 Irradiance

$$
E = \frac{d\Phi}{dA}
$$

单位：$W/m^2$

单位面积接收的功率。

---

### 3.4 Radiant Intensity

$$
I = \frac{d\Phi}{d\omega}
$$

单位：$W/sr$

单位立体角方向上的功率。

---

### 3.5 Solid Angle

$$
\omega = \frac{A}{r^2}
$$

完整球面：

$$
4\pi
$$

半球：

$$
2\pi
$$

---

## 4. Radiance（核心物理量）

$$
L(x,\omega) =
\frac{d^2\Phi}{\cos\theta \, dA \, d\omega}
$$

单位：

$$
W/(m^2\, sr)
$$

含义：

- 单位投影面积
- 单位立体角
- 的功率

性质：

- 在 vacuum 中沿 ray 传播不变
- Path Tracing 实际追踪的量

---

## 5. Radiance 与 Irradiance 关系

$$
E(x) =
\int_{\Omega^+}
L_i(x,\omega_i)\cos\theta_i\, d\omega_i
$$

Irradiance 是半球上 incoming radiance 的积分。

---

## 6. BRDF

定义：

$$
f_r(\omega_i,x,\omega_o)
=
\frac{dL_r(x,\omega_o)}
{dE_i(x,\omega_i)}
$$

或

$$
f_r =
\frac{dL_r}
{L_i \cos\theta_i d\omega_i}
$$

物理意义：

incoming light 从方向 $\omega_i$ 被反射到方向 $\omega_o$ 的比例分布函数。

---

### BRDF 性质

1. Positivity

$$
f_r \ge 0
$$

2. Helmholtz Reciprocity

$$
f_r(\omega_i,\omega_o) =
f_r(\omega_o,\omega_i)
$$

3. Energy Conservation

$$
\int_{\Omega^+}
f_r(\omega_i,\omega_o)
\cos\theta_o\, d\omega_o \le 1
$$

---

## 7. Reflectance Equation

$$
L_r(x,\omega_o)
=
\int_{\Omega^+}
f_r(\omega_i,x,\omega_o)
L_i(x,\omega_i)
\cos\theta_i\, d\omega_i
$$

出射 radiance 等于半球上所有入射 radiance 加权积分。

---

## 8. Rendering Equation

加入自发光项：

$$
L(x,\omega_o)
=
L_e(x,\omega_o)
+
\int_{\Omega^+}
f_r(\omega_i,x,\omega_o)
L_i(x,\omega_i)
\cos\theta_i\, d\omega_i
$$

其中：

$$
L_i(x,\omega_i)
=
L(x',-\omega_i)
$$

形成递归结构。

* $L_e$：自发光 radiance
* $L_i$：incoming radiance 来自其他点的出射 radiance
* $f_r$：BRDF 定义的反射特性，即 incoming → outgoing 的关系
* $\cos\theta_i$：入射角余弦项，表示入射光线与表面法线的夹角对贡献的影响（投影）
* 积分：对半球上所有入射方向进行积分，计算总的出射 radiance
