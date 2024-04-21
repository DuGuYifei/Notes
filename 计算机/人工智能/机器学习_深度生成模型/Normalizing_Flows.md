# Normalizing Flows

1. [Normalizing Flows](#normalizing-flows)
   1. [理解](#理解)
   2. [Change of Variables Formula (变量变换公式)](#change-of-variables-formula-变量变换公式)
      1. [条件](#条件)
      2. [Stacking (叠加)](#stacking-叠加)
      3. [Log-Likelihood (对数似然)](#log-likelihood-对数似然)
   3. [Forward and Reverse Parameterizations (正向和反向参数化)](#forward-and-reverse-parameterizations-正向和反向参数化)
   4. [Jacobian Determinant Computation (雅可比行列式计算)](#jacobian-determinant-computation-雅可比行列式计算)


## 理解
Normalizing Flows（NF）的核心思想是利用可逆变换（flows）将一个复杂的分布变形（变换）为一个简单的分布，通常是高斯分布。

flows的由来是把一个值flow从开始到另一个位置

normalizing是指把一个分布normalize输出空间的概率分布。（归一化）

## Change of Variables Formula (变量变换公式)

补充:
$$det(M^{-1})=det(M)^{-1}$$

1. 对于一维,z属于均值分布[0,1]
   1. ![alt text](_attachments/Normalizing_Flows/image.png)
   2. $$p_2(x)=p_1(z)|f^{-1(1)}(x)|=p_1(z)|f^{(1)}(z)|^{-1}$$
2. 对于2维,向量z属于均值分布$[0,1]^2$
   1. shift
      1. f(z) = z + shift = x
      2. $p_2(x)=p_1(z)
   2. 变形
      1. f(z) = Mz = x, $M=\begin{bmatrix}a & b\\c & d\end{bmatrix}$
         1. 因为对于可逆矩阵有$det(M^{-1})=\frac{1}{det(M)}$
      2. $p_2(x)=p_1(z)|\frac{1}{det(M)}|$ 归一化面积是的概率分布的面积为1
      3. ![alt text](_attachments/Normalizing_Flows/image-1.png)
3. 对于N维
   1. $p_2(x)=p_1(f^{-1}(x))|det(\frac{\partial f^{-1}(x)}{\partial x})|$
   2. 理解：其实就是在每个微点上看成一个linear transformation，然后计算这个linear transformation的雅可比行列式，然后乘以原来的概率密度，得到新的概率密度。之所以是雅可比行列式，是因为雅可比行列式是一个线性变换的distortion rate(畸变率)， 也就是说，如果雅可比行列式大于1，那么这个变换会把原来的空间拉伸，如果小于1，那么这个变换会把原来的空间压缩。也可以说是面积缩放因子，因为雅可比行列式是一个线性变换的面积缩放因子。
   3. $\frac{\partial g(x)}{\partial x}$ 成为Jacobian of g，对于D x D的矩阵:$\frac{\partial f^{-1}(x)}{\partial x}=(\frac{\partial f(z)}{\partial z})^{-1}$
   4. The transformation f should be valid (invertible and differentiable).

### 条件
1. invertible:
   1. 输入和输出必须是一样的dimension
   2. 如果是一维数据，那么f必须是单调的（因为如果不是单调的，那么返回来的数字就不唯一了）
   3. 如果变换是linear的，那么invertible就是det(M) != 0，即M是一个full rank的矩阵或者说可逆矩阵。
2. differentiable:
   1. $f$和$f^{-1}$都是连续可导的，即Jacobian $\frac{\partial f^{-1}(x)}{\partial x}$ 存在于任何点x
   2. 可导是充分条件;理论上来说，f不需要处处可导，比如它是分段函数的时候，范围中间点可以是断开的不可导。
      1. ![alt text](_attachments/Normalizing_Flows/image-2.png)

### Stacking (叠加)

![alt text](_attachments/Normalizing_Flows/image-3.png)

叠加的公式很简单就是连续乘起来就行了，就跟矩阵乘法一样。
$$p_k(x)=p_0(z_0)\prod_{i=1}^{k}|det(\frac{\partial f_i^{-1}(z_i)}{\partial z_i})|=p_0(z)\prod_{i=0}^{k-1}|det((\frac{\partial f_{i}(z_{i})}{\partial z_{i}})^{-1})|$$

### Log-Likelihood (对数似然)

1. 对数似然是一个概率分布的似然函数的对数
2. 使用对数似然是因为概率密度函数的值通常很小，而对数似然可以将这些小的概率密度函数值转换为更大的值，方便计算。

$$log(p_2(x))=log(p_1(z))+log(|det((\frac{\partial f(z)}{\partial z})^{-1})|$$

$$log(p_k(x))=log(p_0(z))+\sum_{i=0}^{k-1}log(|det((\frac{\partial f_{i}(z_{i})}{\partial z_{i}})^{-1})|$$

## Forward and Reverse Parameterizations (正向和反向参数化)

## Jacobian Determinant Computation (雅可比行列式计算)