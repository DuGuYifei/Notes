# 10 Photon Mapping

- [1. 动机（Motivation）](#1-动机motivation)
- [2. 两阶段结构（Two-Pass Algorithm）](#2-两阶段结构two-pass-algorithm)
  - [Pass 1：Photon Shooting（从光源出发）](#pass-1photon-shooting从光源出发)
  - [Pass 2：Rendering（从眼睛出发）](#pass-2rendering从眼睛出发)
- [3. 光子能量定义](#3-光子能量定义)
- [4. Photon Tracing（光子传播）](#4-photon-tracing光子传播)
  - [能量调整](#能量调整)
- [5. Specular 表面特殊处理](#5-specular-表面特殊处理)
- [6. Photon Map 数据结构](#6-photon-map-数据结构)
- [7. Photon Map 存储结构](#7-photon-map-存储结构)
- [8. Radiance Estimate（辐射亮度估计）](#8-radiance-estimate辐射亮度估计)
  - [固定 $n$ vs 固定 $r$](#固定-n-vs-固定-r)
- [9. Filtering（滤波）](#9-filtering滤波)
- [10. 渲染方程分解](#10-渲染方程分解)
- [11. Caustics Photon Map 与 Global Photon Map](#11-caustics-photon-map-与-global-photon-map)
- [12. Photon Mapping vs Radiosity](#12-photon-mapping-vs-radiosity)
- [13. 高级扩展](#13-高级扩展)
  - [1. Dispersion（色散）](#1-dispersion色散)
  - [2. Subsurface Scattering](#2-subsurface-scattering)
  - [3. Participating Media](#3-participating-media)
- [14. 优缺点总结](#14-优缺点总结)
  - [优点](#优点)
  - [缺点](#缺点)
- [15. 本质总结](#15-本质总结)


## 1. 动机（Motivation）

传统 Whitted Ray Tracing 可以处理：

* 直接光照（direct illumination）
* 镜面反射（specular reflection）
* 折射（refraction）

但难以高效处理：

1. 漫反射间接光（Diffuse interreflection）
2. 焦散（Caustics）

焦散路径：

$$
Light \rightarrow Specular \rightarrow Diffuse \rightarrow Eye
$$

在 Path Tracing 中，该路径概率极低，方差极高。

Photon Mapping 的核心思想：

> 从光源出发采样低概率但重要的路径，并将其存储。

---

## 2. 两阶段结构（Two-Pass Algorithm）

Photon Mapping 是一个混合算法。

### Pass 1：Photon Shooting（从光源出发）

* 发射大量光子
* 在场景中传播
* 当光子击中非 perfect specular 表面时：

  * 存储其位置
  * 存储入射方向
  * 存储光子功率
* 构建加速结构（通常为 Kd-tree）

方向：

$$
Light \rightarrow Scene
$$

---

### Pass 2：Rendering（从眼睛出发）

* 使用常规 ray tracing
* 在交点处查询 photon map
* 使用密度估计计算间接光

方向：

$$
Eye \rightarrow Scene
$$

---

## 3. 光子能量定义

设：

* $n_e$：发射光子数量
* $\Phi_{light}$：光源总功率

每个光子的功率：

$$
\Phi_{photon} = \frac{\Phi_{light}}{n_e}
$$

采用 constant photon energy。

---

## 4. Photon Tracing（光子传播）

光子击中表面后：

* 吸收（absorption）
* 漫反射（diffuse）
* 镜面反射（specular）

使用 Russian Roulette：

设材料参数：

* $\rho_d$：漫反射率
* $\rho_s$：镜面反射率

要求：

$$
\rho_d + \rho_s \le 1
$$

随机数 $x \in [0,1]$：

* 若 $x < \rho_d$ → diffuse
* 若 $\rho_d < x < \rho_d + \rho_s$ → specular
* 否则 → absorption

---

### 能量调整

入射光子功率：

$$
\Phi_i
$$

输出功率：

$$
\Phi_o = \Phi_i (\rho_d + \rho_s)
$$

在 RGB 通道上独立处理：

$$
\rho_{d,i} + \rho_{s,i} \le 1, \quad i \in {R,G,B}
$$

---

## 5. Specular 表面特殊处理

Perfect specular 表面：

* 不存储 photon
* 继续沿反射/折射方向传播

原因：

Specular BRDF 是 delta 分布，无法通过密度估计恢复。

---

## 6. Photon Map 数据结构

每个 photon 存储：

* 位置 $(x,y,z)$
* 入射方向（量化球坐标）
* 光子功率 $(r,g,b)$

方向量化示例：

$$
\theta = 255 \cdot \frac{\arccos(d_z)}{\pi}
$$

$$
\phi = 255 \cdot \frac{\arctan2(d_y,d_x)+\pi}{2\pi}
$$

---

## 7. Photon Map 存储结构

可选结构：

1. Array：$O(n)$ 查询
2. Grid：$O(1)$ 查询，内存大
3. Kd-tree：$O(\log n)$ 查询（推荐）

通常使用 balanced Kd-tree。

---

## 8. Radiance Estimate（辐射亮度估计）

在交点 $x$：

搜索最近 $n$ 个 photon。

估计公式：

$$
L(x,\omega_o)
\approx
L_e(x,\omega_o)
+
\sum_{p=1}^{n}
f(\omega_p,x,\omega_o)
\frac{\Delta \Phi_p}{\Delta A}
$$

若局部近似平面：

$$
\Delta A = \pi r^2
$$

得到：

$$
L(x,\omega_o)
\approx
L_e
+
\frac{1}{\pi r^2}
\sum_{p=1}^{n}
f(\omega_p,x,\omega_o)
\Delta \Phi_p
$$

这是 Kernel Density Estimation。

---

### 固定 $n$ vs 固定 $r$

* 固定 $n$（k-NN） → 半径自适应（推荐）
* 固定 $r$ → 光子数变化

---

## 9. Filtering（滤波）

等权平均会造成：

* 边缘模糊
* 错误 color bleeding

使用加权核函数，例如 cone kernel：

$$
w_p = 1 - \frac{d_p}{k r}
$$

估计：

$$
L(x) \approx
\frac{1}{\sum w_p}
\sum w_p \Delta \Phi_p
$$

---

## 10. 渲染方程分解

BRDF 分解：

$$
f = f_s + f_d
$$

入射光分解：

$$
L_i = L_d + L_c + L_{id}
$$

渲染方程：

$$
L_r(x,\omega_o)
===============

\int_{\Omega^+}
f(\omega_i,x,\omega_o)
L_i(x,\omega_i)
\cos\theta_i
, d\omega_i
$$

对应计算方式：

* $L_d$：shadow ray
* $f_s$：递归 ray tracing
* $L_c$：caustics photon map
* $L_{id}$：global photon map

---

## 11. Caustics Photon Map 与 Global Photon Map

通常维护两个 photon map：

1. Caustics map

   * 只存 Light→Specular→Diffuse 路径
2. Global map

   * 存多次漫反射

---

## 12. Photon Mapping vs Radiosity

| 特性                | Photon Mapping | Radiosity            |
| ----------------- | -------------- | -------------------- |
| 焦散                | 支持             | 不支持                  |
| Specular          | 支持             | 不支持                  |
| View independence | 部分             | 完全                   |
| 噪声                | 有（低方差）         | 无                    |
| 几何表示              | 无需 patch       | 需要 patch subdivision |

Photon mapping 更通用，但有偏。

---

## 13. 高级扩展

### 1. Dispersion（色散）

折射率随波长变化：

$$
\eta = \eta(\lambda)
$$

需要 spectral photon mapping。

---

### 2. Subsurface Scattering

使用 volume photon map。

涉及 BSSRDF，而非 BRDF。

---

### 3. Participating Media

在体积中存储 photon。

用于：

* 体积焦散
* God rays
* 雾、烟效果

---

## 14. 优缺点总结

### 优点

* 高效处理焦散
* 低方差
* 可扩展至体积与光谱

### 缺点

* 有偏估计
* 参数敏感（$n$、$r$）
* 内存需求高
* 光源或场景改变需重建 photon map

---

## 15. 本质总结

Photon Mapping 是：

> Forward Light Transport + Density Estimation

是一种：

* 有偏
* 低方差
* 混合式全局光照算法

核心数学基础：

* Monte Carlo 采样
* Russian Roulette
* Kernel Density Estimation
* Rendering Equation 分解
