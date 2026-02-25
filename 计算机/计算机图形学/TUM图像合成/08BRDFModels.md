# 08 BRDF Models

- [0. 总目标](#0-总目标)
- [1. BRDF 模型分类](#1-brdf-模型分类)
- [2. 为什么 Phong 不够“物理”](#2-为什么-phong-不够物理)
- [3. Microfacet 核心几何：half vector](#3-microfacet-核心几何half-vector)
- [4. Torrance–Sparrow（Cook–Torrance）镜面 BRDF 总公式](#4-torrancesparrowcooktorrance镜面-brdf-总公式)
  - [4.1 分母中的 $(n\\cdot l)$ 与 $(n\\cdot v)$](#41-分母中的-ncdot-l-与-ncdot-v)
- [5. F：Fresnel term（光学项）——“反射多少”](#5-ffresnel-term光学项反射多少)
- [6. D：Normal Distribution Function（统计项）——“有多少 facet 朝向 h”](#6-dnormal-distribution-function统计项有多少-facet-朝向-h)
- [7. G：Geometry term（几何可见性）——“能看见多少 facet”](#7-ggeometry-term几何可见性能看见多少-facet)
- [8. 金属反射（为什么 microfacet + Fresnel 必要）](#8-金属反射为什么-microfacet--fresnel-必要)
- [9. Measured BRDF 与工具](#9-measured-brdf-与工具)
- [10. 超出 BRDF：Subsurface effects](#10-超出-brdfsubsurface-effects)


## 0. 总目标
用物理合理的方式描述表面反射(这里只讲解 specular 部分，其他比如 diffuse 部分可以用 Lambertian 模型)：用 BRDF $f_r(\omega_i,\omega_o)$ 把入射方向 $\omega_i$ 的辐照/辐亮度转成出射方向 $\omega_o$ 的辐亮度。
渲染里常用关系：
$$
L_o = f_r(\omega_i,\omega_o)\,(n\cdot l)\,L_i
$$

---

## 1. BRDF 模型分类
- Ideal：Perfect specular；Lambertian diffuse
- Empirical：Phong 等现象学模型
- Experimental：用测量设备（goniometer）得到 measured BRDF
- Theoretical：基于 microfacet theory（Torrance–Sparrow / Cook–Torrance）

---

## 2. 为什么 Phong 不够“物理”
Phong specular（启发式）：
$$
L_r = k_s(\mathbf{r}\cdot\mathbf{v})^n L_i
$$
若硬改写成 BRDF 形式：
$$
f_r =
\frac{k_s(\mathbf{r}\cdot\mathbf{v})^n}{(n\cdot l)}
$$
问题：
- 不保证能量守恒（缺少正确归一化）
- 不满足 Helmholtz reciprocity（交换 $\omega_i,\omega_o$ 不对称）

---

## 3. Microfacet 核心几何：half vector
把宏观表面看成许多“完美镜面”的微小平面（microfacets），每个 facet 有法线 $\mathbf{m}$。
只有满足镜面条件的 facets 才能把光从 $\mathbf{l}$ 反射到 $\mathbf{v}$。
定义 half vector：
$$
\mathbf{h} = \frac{\mathbf{l}+\mathbf{v}}{\|\mathbf{l}+\mathbf{v}\|}
$$
可见贡献来自满足：
$$
\mathbf{m}=\mathbf{h}
$$
的 microfacets（统计意义上“法线接近 $\mathbf{h}$”）。

---

## 4. Torrance–Sparrow（Cook–Torrance）镜面 BRDF 总公式
$$
f_s(\mathbf{l},\mathbf{v})
=
\frac{F(\cdot)\,D(\mathbf{h})\,G(\mathbf{l},\mathbf{v},\mathbf{h})}
{\pi (n\cdot l)(n\cdot v)}
$$
理解方式：$\boxed{F\cdot D\cdot G}$ /（几何归一化项）

### 4.1 分母中的 $(n\cdot l)$ 与 $(n\cdot v)$
- $(n\cdot l)$：光源方向看到的有效投影面积（入射 foreshortening）
- $(n\cdot v)$：观察方向看到的有效投影面积（出射 foreshortening / 面积变换）
- $\pi$：与归一化、半球积分约束相关（保证能量行为正确）

---

## 5. F：Fresnel term（光学项）——“反射多少”
物理意义：在给定角度下，入射光有多少比例被反射（其余折射/透射）。
- 值域：$0\le F\le 1$
- 典型现象：掠射角（grazing）反射增强，边缘更亮

精确 Fresnel：
- Snell 定律：
$$
s_i\sin\theta_i = s_t\sin\theta_t
$$
- 反射率与偏振相关，非偏振光：
$$
R = \frac{r_\perp+r_\parallel}{2},\quad T=1-R
$$

Schlick 近似（工程常用）：
$$
F(\theta)=F_0+(1-F_0)(1-\cos\theta)^5
$$
实现中常取：
$$
\cos\theta = \mathbf{v}\cdot\mathbf{h}
$$

---

## 6. D：Normal Distribution Function（统计项）——“有多少 facet 朝向 h”
物理意义：microfacet 法线分布的概率密度（NDF）。
- 控制高光“宽/窄”，对应 roughness
- 必须归一化以满足能量守恒

Beckmann 分布（例）：
- $\beta=\angle(\mathbf{h},\mathbf{n})$，$r$ 为 roughness
$$
D(\mathbf{h})
=
\frac{\exp\left(-\left(\frac{\tan\beta}{r}\right)^2\right)}
{4r^2\cos^4\beta}
$$
趋势：$r$ 越大 → 分布越宽 → 高光越粗糙。

---

## 7. G：Geometry term（几何可见性）——“能看见多少 facet”
原因：即使 $\mathbf{m}\approx\mathbf{h}$，也可能不可见：
- Shadowing：从光源看被遮挡（照不到）
- Masking：从视角看被遮挡（看不到）

$G$ 的作用：
- 把被遮挡的 facets 去掉
- 值域：$0\le G\le 1$
- 对能量守恒很关键
- 常见：Smith 类几何项（课程只强调意义）

---

## 8. 金属反射（为什么 microfacet + Fresnel 必要）
金属（导体）：
- 漫反射几乎为 0
- specular 反射强且常带颜色（来自 Fresnel/F0 的谱特性）
因此 Phong 难以真实表现银/铜/金/铂的颜色型高光，microfacet 可以。

---

## 9. Measured BRDF 与工具
- BRDF 是 4D：$f_r(\theta_i,\phi_i,\theta_o,\phi_o)$
- 可用测量设备得到数据，形成材料数据库
- 数据量大 → 需要压缩（含 DL compaction）
- Differentiable rendering：从图像反推材质/BRDF 参数
- BRDFlab：用于设计、拟合、可视化与渲染验证 BRDF

---

## 10. 超出 BRDF：Subsurface effects
BRDF 假设入射与出射发生在同一点（局部表面模型）。
若光进入材质内部散射后从别处出来（皮肤、蜡等），需要：
- BSSRDF（空间非局部散射模型）