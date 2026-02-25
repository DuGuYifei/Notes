# 14 Graphical Models

- [一、几何表示（Geometric Models）](#一几何表示geometric-models)
  - [1.1 几何模型分类](#11-几何模型分类)
    - [（1）自由形状曲面（Free-form Surfaces）](#1自由形状曲面free-form-surfaces)
    - [（2）构造实体几何（CSG）](#2构造实体几何csg)
    - [（3）体素模型（Voxel Models）](#3体素模型voxel-models)
    - [（4）点模型（Point Models）](#4点模型point-models)
- [二、体素模型（Voxel Models）](#二体素模型voxel-models)
  - [2.1 基本定义](#21-基本定义)
  - [2.2 光线遍历（Ray Traversal）](#22-光线遍历ray-traversal)
    - [方法1：逐步检测 iso-surface](#方法1逐步检测-iso-surface)
    - [方法2：三线性插值](#方法2三线性插值)
  - [2.3 Level of Detail（LoD）](#23-level-of-detaillod)
  - [2.4 Sparse Voxel Octree（SVO）](#24-sparse-voxel-octreesvo)
  - [2.5 SVO 渲染策略](#25-svo-渲染策略)
  - [2.6 Hybrid Rendering](#26-hybrid-rendering)
- [三、点模型渲染](#三点模型渲染)
  - [3.1 点渲染问题](#31-点渲染问题)
  - [3.2 球体渲染方法](#32-球体渲染方法)
  - [3.3 等值面重建（Density Field）](#33-等值面重建density-field)
  - [3.4 图像空间平滑](#34-图像空间平滑)
  - [3.5 2D Gaussian Splatting](#35-2d-gaussian-splatting)
- [四、正向渲染与逆渲染](#四正向渲染与逆渲染)
  - [4.1 正向渲染](#41-正向渲染)
  - [4.2 逆渲染](#42-逆渲染)
- [五、Radiance Field](#五radiance-field)
  - [5.1 体积渲染公式](#51-体积渲染公式)
- [六、Neural Radiance Fields（NeRF）](#六neural-radiance-fieldsnerf)
  - [6.1 表示方式](#61-表示方式)
  - [6.2 渲染流程](#62-渲染流程)
  - [6.3 优化目标](#63-优化目标)
  - [6.4 NeRF 特性](#64-nerf-特性)
- [七、3D Gaussian Splatting（3DGS）](#七3d-gaussian-splatting3dgs)
  - [7.1 表示](#71-表示)
  - [7.2 特点](#72-特点)
  - [7.3 渲染](#73-渲染)
  - [7.4 逆渲染优化](#74-逆渲染优化)
- [八、整体技术演化路线](#八整体技术演化路线)
- [九、考试核心理解点](#九考试核心理解点)
- [十、NeRF vs 3DGS 对比](#十nerf-vs-3dgs-对比)


## 一、几何表示（Geometric Models）

### 1.1 几何模型分类

三维对象的数学表示方式：

#### （1）自由形状曲面（Free-form Surfaces）

* 用有限个控制参数描述连续曲面
* 常见形式：Bezier、B-Spline、NURBS
* 特点：

  * 表达精确
  * 模型高度压缩
  * 适合 CAD 建模
* 本质：参数化连续曲面

---

#### （2）构造实体几何（CSG）

* 通过布尔运算构造复杂形体：

  * Union
  * Intersection
  * Difference
* 表示形式为布尔树
* 适合规则机械结构

本质：

> 基本体 + 集合运算

---

#### （3）体素模型（Voxel Models）

* 将空间离散为三维规则网格
* 每个格子记录：

  * 是否在物体内部
  * 或记录密度值

存储复杂度：
$$
O(n^3)
$$

问题：

* 空间浪费严重

---

#### （4）点模型（Point Models）

* 使用点云表示物体
* 每个点包含：

  * 位置
  * 法线
  * 颜色

优点：

* 适合扫描数据

问题：

* 空洞
* 遮挡处理困难

---

## 二、体素模型（Voxel Models）

### 2.1 基本定义

将空间离散为立方体网格。

对每个 cell 判断：

* 是否在物体内部
* 是否与表面相交

---

### 2.2 光线遍历（Ray Traversal）

光线表达式：

$$
\mathbf{r}(t) = \mathbf{s} + t\mathbf{D}
$$

#### 方法1：逐步检测 iso-surface

判断符号变化：

$$
(val(\mathbf{s}+t\mathbf{D}) - isoVal)(val(\mathbf{s}+(t+dt)\mathbf{D}) - isoVal) < 0
$$

然后二分搜索。

---

#### 方法2：三线性插值

体素内部：

$$
\rho(u,v,w) = \sum_{i,j,k \in {0,1}} u_i v_j w_k \rho_{ijk}
$$

代入射线得到：

$$
\rho(t) = isoVal
$$

得到三次方程。

---

### 2.3 Level of Detail（LoD）

思想：

* 建立多分辨率体素副本
* 选择投影尺寸接近像素大小的层级

原则：

> 投影体素尺寸 ≈ 像素大小

---

### 2.4 Sparse Voxel Octree（SVO）

问题：

$$
O(n^3)
$$

解决：

* 使用八叉树
* 只细化包含表面的区域

优点：

* 自适应分辨率
* 节省存储

---

### 2.5 SVO 渲染策略

距离增大：

* 光线间距增大
* 使用更粗层级采样

核心思想：

> 远处采样粗分辨率

---

### 2.6 Hybrid Rendering

在叶子节点中存储三角形：

* 当体素分辨率不足时
* 切换为三角形渲染

---

## 三、点模型渲染

### 3.1 点渲染问题

* 像素级点 → 存在空洞
* 遮挡穿透

---

### 3.2 球体渲染方法

三种方式：

1. 几何球体
2. 屏幕空间 quad + 像素着色器
3. 光线追踪球体（BVH）

---

### 3.3 等值面重建（Density Field）

假设每个球有密度 $D_j$。

任意点密度：

$$
D_i = \sum_j D_j W_{ij}
$$

核函数：

$$
W_{ij} = \frac{1}{2\pi\sigma^2} e^{-\frac{x^2+y^2+z^2}{2\sigma^2}}
$$

寻找 iso-value。

---

### 3.4 图像空间平滑

最小化：

$$
\arg\min_u \int_\Omega |\nabla u(x)|^2 + \frac{1}{2\lambda}(u(x)-v(x))^2
$$

意义：

* 平滑图像
* 保持与原图接近

---

### 3.5 2D Gaussian Splatting

* 点投影为 2D Gaussian
* 使用协方差矩阵 $\Sigma$
* 屏幕空间混合

---

## 四、正向渲染与逆渲染

### 4.1 正向渲染

$$
I = \mathcal{R}(\Phi)
$$

输入：

* 形状
* 材质
* 光照
* 相机

输出：

* 图像

---

### 4.2 逆渲染

$$
\Phi = \mathcal{R}^{-1}(I)
$$

目标：

* 根据图像优化场景参数

关键：

* 可微渲染
* 自动求导

---

## 五、Radiance Field

### 5.1 体积渲染公式

$$
C(\mathbf{r}) = \int_{t_{in}}^{t_{out}} T(t)\sigma(\mathbf{r}(t))c(\mathbf{r}(t),\mathbf{d}) dt
$$

其中：

* $\sigma(x)$：密度
* $c(x,d)$：颜色
* $T(t)$：透射率

本质：

> 沿光线积分体密度与颜色

---

## 六、Neural Radiance Fields（NeRF）

### 6.1 表示方式

输入：

$$
(x,y,z,\theta,\phi)
$$

输出：

$$
\sigma(x), c(x,d)
$$

使用 MLP 表示。

---

### 6.2 渲染流程

1. 沿射线采样：

$$
x_i = o + (t_{in} + \delta i)d
$$

2. 网络预测：

$$
F(\theta; x_i)
$$

3. 体积混合：

$$
c = B(F)
$$

---

### 6.3 优化目标

每个像素对应一条射线：

$$
\min_\theta \sum_i L(B(F(\theta;S(x_i))), y_i)
$$

使用 SGD：

$$
\theta \leftarrow \theta - \lambda \nabla_\theta L
$$

---

### 6.4 NeRF 特性

* 光照 baked-in
* 支持视角相关颜色
* 渲染慢（需体积积分）

---

## 七、3D Gaussian Splatting（3DGS）

### 7.1 表示

每个高斯包含：

* 位置 $p$
* 协方差矩阵 $\Sigma$
* 不透明度 $\alpha$
* SH 系数

协方差矩阵：

$$
\Sigma =
\begin{bmatrix}
\sigma_x & \sigma_{xy} & \sigma_{xz} \\
\sigma_{yx} & \sigma_y & \sigma_{yz} \\
\sigma_{zx} & \sigma_{zy} & \sigma_z
\end{bmatrix}
$$

---

### 7.2 特点

* 各向异性
* 稀疏
* 不需 ray marching

---

### 7.3 渲染

步骤：

1. 投影到 2D
2. 变为 2D Gaussian
3. 排序
4. alpha blending

---

### 7.4 逆渲染优化

可微 rasterization：

$$
\frac{\partial I}{\partial p},
\frac{\partial I}{\partial \Sigma},
\frac{\partial I}{\partial \alpha}
$$

通过链式法则更新参数。

---

## 八、整体技术演化路线

```
三角形网格
→ 体素
→ 稀疏体素
→ 可微体积
→ NeRF
→ 3D Gaussian Splatting
```

核心思想演进：

```
显式几何
→ 离散体积
→ 连续密度场
→ 可学习密度场
→ 可微高斯分布表示
```

---

## 九、考试核心理解点

必须掌握：

1. 体素 vs 网格区别
2. 三线性插值
3. 体积渲染公式
4. 正向与逆渲染关系
5. NeRF 渲染流程
6. SGD 优化原理
7. 3DGS 与 NeRF 的区别

---

## 十、NeRF vs 3DGS 对比

| 特性   | NeRF         | 3DGS          |
| ---- | ------------ | ------------- |
| 表示   | MLP          | 高斯集合          |
| 渲染   | Ray marching | Rasterization |
| 速度   | 慢            | 快             |
| 稀疏性  | 隐式           | 显式            |
| 可解释性 | 低            | 高             |

---

