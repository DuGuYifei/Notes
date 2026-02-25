# 02 Texture Mapping Issues

- [前言](#前言)
- [Anisotropic Filtering（各向异性过滤）](#anisotropic-filtering各向异性过滤)
  - [1. Texture-space derivatives（纹理空间导数）](#1-texture-space-derivatives纹理空间导数)
  - [2. LOD 计算（按 slide）](#2-lod-计算按-slide)
  - [3. 为什么N约等于采样次数](#3-为什么n约等于采样次数)
  - [4. 采样方向（major axis）](#4-采样方向major-axis)
- [Perspective-Correct Interpolation（透视正确插值）](#perspective-correct-interpolation透视正确插值)
  - [1. 问题](#1-问题)
  - [2. 正确方法](#2-正确方法)
  - [3. $w$ 的含义](#3-w-的含义)
  - [4. 原理理解](#4-原理理解)


## 前言

根据提供的课程记录，老师在课程开始部分确实回顾并深入讲解了 **Mipmap（多级渐远纹理）** 的相关概念。他主要涵盖了以下几个核心内容：

**1. Mipmap 的基本定义与结构**
*   **分层结构**：Mipmap 是一种分层的数据结构。最底层是原始分辨率的纹理（例如 256x256 像素），往上每一层的分辨率在长宽方向上都减半（例如变成 128x128，然后 64x64），直到缩减为 1x1。
*   **生成方式**：较高层级的纹理通常是通过对下一层对应的四个纹素（Texels）取平均值（低通滤波）来生成的。

**2. Mipmap 解决的核心问题：走样 (Aliasing)**
*   **点采样的缺陷**：老师解释了当物体离相机较远或有透视缩放时，屏幕上的一个像素（Pixel）实际上会覆盖纹理空间中的多个纹素。如果仅仅进行“点采样”（只取像素中心对应的那个纹素颜色），就无法代表该区域的整体颜色，从而导致走样（Aliasing）。
*   **匹配尺寸**：Mipmap 的目的是找到一个层级，使得该层级上的纹素大小在投影到屏幕后，大致等于屏幕像素的大小。这样采样时就能获得更准确的颜色平均值。

**3. 采样的平滑处理：三线性插值 (Trilinear Interpolation)**
*   **层级突变**：如果直接在离散的 Mipmap 层级之间切换（例如从第 0 层直接跳到第 1 层），会在视觉上产生明显的接缝或突变。
*   **解决方案**：老师提到了**三线性插值**技术。它通过在两个最接近的 Mipmap 层级上分别进行双线性插值，然后在这两个结果之间再进行一次线性插值，从而实现层级间的平滑过渡。

**4. Mipmap 的局限性与各向异性过滤 (Anisotropic Filtering)**
*   老师在讲完基础 Mipmap 后，重点指出了它的一个缺陷：它假设像素在纹理空间覆盖的区域是正方形的（各向同性）。
*   **倾斜视角的模糊**：当观察倾斜的表面时，像素在纹理上的投影实际上是一个细长的矩形或梯形。标准的 Mipmap 会根据长边来选择模糊程度较高的层级，导致图像在短边方向过度模糊。
*   这引出了后续关于**各向异性过滤**的讲解，即通过在纹理空间沿“各向异性线”进行多次采样来保持倾斜表面的纹理清晰度。

总结来说，老师讲 Mipmap 是为了解释计算机图形学中如何通过预计算不同分辨率的纹理来解决**采样走样**的问题，并以此作为铺垫，引出了更高级的**各向异性过滤**技术。

## Anisotropic Filtering（各向异性过滤）

### 1. Texture-space derivatives（纹理空间导数）

设片元的纹理坐标为 $(u(x,y), v(x,y))$，其中 $(x,y)$ 是 screen space 像素坐标。

定义：

$$
d_x = \left| \left( \frac{\partial u}{\partial x}, \frac{\partial v}{\partial x} \right) \right|
$$

$$
d_y = \left| \left( \frac{\partial u}{\partial y}, \frac{\partial v}{\partial y} \right) \right|
$$

再定义：

$$
p_{\max} = \max(d_x, d_y)
$$

$$
p_{\min} = \min(d_x, d_y)
$$

Anisotropy ratio（各向异性比例）：

$$
N = \left\lceil \frac{p_{\max}}{p_{\min}} \right\rceil
$$

这里的取整表示向上取整，这是课程里的定义，实际上计算我认为不取整也是可以的，因为是用来计算后面的LOD level的，当然采样肯定是整数个。

含义：

* $p_{\max}$：footprint 的 long axis 长度
* $p_{\min}$：footprint 的 short axis 长度
* $N$：拉伸比例

---

### 2. LOD 计算（按 slide）

$$
\text{LOD} = \log_2 \left( \frac{p_{\max}}{N} \right)
$$

由于：

$$
\frac{p_{\max}}{N} = p_{\min}
$$

等价于：

$$
\text{LOD} = \log_2(p_{\min})
$$

理解：

* LOD 按 short axis 决定
* long axis 通过 multi-sampling 处理

---

### 3. 为什么N约等于采样次数

几何解释：

* short axis ≈ $p_{\min}$
* long axis ≈ $p_{\max}$
* 比例 $N = p_{\max} / p_{\min}$

如果一个 sample 覆盖 short axis 的宽度，
要覆盖 long axis 需要约 $N$ 个 sample。

硬件使用整数采样数：

$$
n_{\text{taps}} = \mathrm{clamp}(\lfloor N \rceil, 1, A_{\max})
$$

其中：

* $\lfloor N \rceil$ 表示取整（通常 round 或 floor）
* $A_{\max}$ 是最大支持的 anisotropy（如 8 或 16）

---

### 4. 采样方向（major axis）

选择较大的导数方向：

* 若 $d_x \ge d_y$ → major = $\left( \frac{\partial u}{\partial x}, \frac{\partial v}{\partial x} \right)$
* 否则 → major = $\left( \frac{\partial u}{\partial y}, \frac{\partial v}{\partial y} \right)$

归一化：

$$
\hat{m} = \frac{\text{major}}{|\text{major}|}
$$

采样点围绕中心 $p$ 对称分布：

$$
p_i = p + t_i , \Delta , \hat{m}
$$

其中 $t_i$ 为对称偏移（$-k \ldots +k$），
因此采样是 centered，而不是单方向。

---

## Perspective-Correct Interpolation（透视正确插值）

### 1. 问题

Perspective projection：

$$
x' = \frac{x}{w}
$$

除以 $w$ 是非线性操作，
因此 screen space 中的线性插值是错误的。

---

### 2. 正确方法

在 vertex 阶段：

$$
p' = \frac{p}{w}
$$

$$
q' = \frac{1}{w}
$$

在 screen space 线性插值：

$$
p'*{\text{interp}}, \quad q'*{\text{interp}}
$$

最终恢复：

$$
p_{\text{correct}} = \frac{p'*{\text{interp}}}{q'*{\text{interp}}}
$$

---

### 3. $w$ 的含义

* $w$ 是 clip space 的 homogeneous coordinate
* 在标准透视投影中，$w \propto z_{\text{camera}}$
* 除以 $w$ 实现 perspective scaling

---

### 4. 原理理解

* Rasterizer 只能做 linear interpolation
* 直接插值 $p$ 会产生透视误差
* 先插值 $p/w$，再除以插值后的 $1/w$，
  可以抵消 perspective projection 的非线性影响