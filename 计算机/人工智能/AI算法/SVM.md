# SVM

[学习SVM，这篇文章就够了！（附详细代码）](https://www.jiqizhixin.com/articles/2018-10-17-20)

[【机器学习】支持向量机 SVM（非常详细）](https://zhuanlan.zhihu.com/p/77750026)
[Python机器学习笔记：SVM（1）——SVM概述 - 战争热诚 - 博客园](https://www.cnblogs.com/wj-1314/p/12899598.html)
[Python机器学习笔记：SVM（2）——SVM核函数 - 战争热诚 - 博客园](https://www.cnblogs.com/wj-1314/p/12931799.html)

- 二分类

- 寻找距离**支持向量**最远的分类超平面
  ![](2022-07-25-01-41-08.png)

- 一般选择线性核函数，效果不好上高斯核函数，高斯核函数可以映射到无限维空间

- 核函数(Kernel function)
    1. 线性核函数

    2. 多项式核函数

    3. 高斯核函数
    ![](2022-07-25-03-07-52.png)


    这三个常用的核函数中只有高斯核函数是需要调参的。

    这里简单说一下核函数与其他参数的作用（后面会详细学习关于使用Sklearn学习SVM）：

    - kernel='linear' 时，C越大分类效果越好，但有可能会过拟合（default C=1）
    - kernel='rbf'时，为高斯核，gamma值越小，分类界面越连续；gamma值越大，分类界面越“散”，分类效果越好，但有可能  会过拟合。
