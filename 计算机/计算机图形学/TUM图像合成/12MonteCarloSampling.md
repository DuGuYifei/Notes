# 12 Monte Carlo Sampling


## 1. Path Tracing 基本思想

### 1.1 渲染方程

$$
L_o(x,\omega_o)
=
\int_{\Omega^+}
f_r(x,\omega_i,\omega_o)\,
L_i(x,\omega_i)\,
\cos\theta
\, d\omega_i
$$

- $f_r$：BRDF  
- $L_i$：入射光  
- $\cos\theta$：几何项  

这是一个半球积分，通常无法解析求解。

---

### 1.2 Monte Carlo 估计

将积分写为期望形式：

$$
I = \int f(x)\, dx
=
\int \frac{f(x)}{p(x)} p(x)\, dx
$$

Monte Carlo estimator：

$$
\hat{I}
=
\frac{1}{N}
\sum_{i=1}^N
\frac{f(x_i)}{p(x_i)}
\quad
x_i \sim p(x)
$$

在 Path Tracing 中：

$$
L_o
\approx
\frac{1}{N}
\sum
\frac{
f_r(\omega_i)
L_i(\omega_i)
\cos\theta_i
}{
p(\omega_i)
}
$$

---

## 2. Monte Carlo 性质

### 2.1 无偏性

$$
\mathbb{E}[\hat{I}] = I
$$

只要 $p(x) > 0$ 在 $f(x) \neq 0$ 区域成立。

---

### 2.2 方差

$$
\mathrm{Var}[\hat{I}]
=
\frac{1}{N}
\left(
\int \frac{f(x)^2}{p(x)} dx
-
I^2
\right)
$$

收敛率：

$$
\epsilon \sim O\left(\frac{1}{\sqrt{N}}\right)
$$

噪声降低一半需要 4 倍样本。

---

## 3. Importance Sampling

### 3.1 动机

目标：

$$
p(x) \approx \frac{|f(x)|}{\int |f(x)| dx}
$$

若：

$$
p(x) \propto f(x)
$$

则：

$$
\frac{f(x)}{p(x)}
\approx \text{常数}
$$

方差最小。

---

### 3.2 漫反射示例

Lambertian：

$$
f_r = \frac{\rho}{\pi}
$$

积分：

$$
L_o
=
\int
\frac{\rho}{\pi}
L_i
\cos\theta
\, d\omega
$$

使用：

$$
p(\omega) = \frac{\cos\theta}{\pi}
$$

则：

$$
\hat{L}
=
\frac{1}{N}
\sum \rho L_i
$$

$\cos\theta$ 被消去，方差显著降低。

---

## 4. PDF 与 CDF

### 4.1 PDF 条件

$$
p(x) \ge 0
$$

$$
\int p(x)\, dx = 1
$$

---

### 4.2 CDF 定义

$$
P(x)
=
\int_{-\infty}^x p(t)\, dt
$$

区间概率：

$$
P(a \le X \le b)
=
P(b) - P(a)
$$

---

### 4.3 关系

$$
p(x) = \frac{dP(x)}{dx}
$$

---

## 5. 反变换采样（Inverse Transform Sampling）

若：

$$
\xi \sim U(0,1)
$$

则：

$$
x = P^{-1}(\xi)
$$

满足：

$$
x \sim p(x)
$$

步骤：

1. 写出 $p(x)$  
2. 计算 $P(x)$  
3. 求反函数  

---

## 6. 重要采样实例

### 6.1 $p(x) \propto x^2$

区间 $[a,b]$

归一化常数：

$$
c = \frac{b^3 - a^3}{3}
$$

PDF：

$$
p(x) = \frac{x^2}{c}
$$

CDF：

$$
P(x)
=
\frac{x^3 - a^3}{b^3 - a^3}
$$

反函数：

$$
x =
\left(
a^3 + \xi (b^3 - a^3)
\right)^{1/3}
$$

---

### 6.2 $p(x) = \cos(x)$

区间 $[0,\pi/2]$

$$
P(x) = \sin(x)
$$

反函数：

$$
x = \arcsin(\xi)
$$

---

## 7. Cosine-weighted Hemisphere Sampling

### 7.1 目标 PDF

$$
p(\omega)
=
\frac{\cos\theta}{\pi}
$$

---

### 7.2 Malley 方法

1. 在单位圆盘均匀采样 $(x,y)$  
2. 投影到半球：

$$
z = \sqrt{1 - x^2 - y^2}
$$

得到方向：

$$
\omega = (x,y,z)
$$

---

## 8. Russian Roulette

为避免固定截断产生 bias：

$$
F' =
\begin{cases}
\frac{F}{1-q}, & \xi > q \\
0, & \text{otherwise}
\end{cases}
$$

期望：

$$
\mathbb{E}[F'] = F
$$

无偏，但方差增大。

---

## 9. 体渲染中的 Monte Carlo

体渲染方程：

$$
L(x,\omega)
=
\int_0^d
T(t)
\left(
\sigma_a L_e
+
\sigma_s L_s
\right)
dt
+
T(d)L_d
$$

透射率：

$$
T(t)
=
\exp
\left(
-
\int_0^t
\sigma_t ds
\right)
$$

均匀介质自由路径采样：

$$
p(t) = \sigma_t e^{-\sigma_t t}
$$

反函数：

$$
t = -\frac{\ln \xi}{\sigma_t}
$$

---

## 10. 核心总结

1. Monte Carlo 将积分转为随机变量期望  
2. 收敛率为 $O(1/\sqrt{N})$  
3. Importance sampling 降低方差  
4. PDF 决定采样策略  
5. CDF 反函数用于生成随机变量  
6. Path tracing 是路径空间上的 Monte Carlo  
7. Russian roulette 保证无偏提前终止  
8. 体渲染中距离采样本质是指数分布  

---

## 最核心公式

$$
\hat{I}
=
\frac{1}{N}
\sum
\frac{f(x_i)}{p(x_i)}
$$

这就是整套 Monte Carlo 光传输算法的数学核心。