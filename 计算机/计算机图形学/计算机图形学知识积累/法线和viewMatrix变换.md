# 法线和viewMatrix变换

## 公式
正常的顶点变换只需要用点乘viewMatrix即可，但是法线变换需要用到viewMatrix的逆矩阵的转置矩阵。

即:

$$N_{world} = (viewMatrix^{-1})^T \cdot N_{local}$$

## 推导
V是切线向量，N是原本的法向量，因为垂直，所以：

$$N^T*V = 0$$

$$N_{world}^T*V_{world} = 0$$

开始推导, M是viewModel：

$$N^T*M^{-1}*M*V = 0$$

$$((M^{-1})^T*N)^T*V_{world} = 0$$

和第二个公式对比，可以得到：

$$N_{world} = (M^{-1})^T*N$$