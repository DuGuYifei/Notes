# Logistic Regression

逻辑回归（Logistic Regression）是一种常用的二分类算法，用于预测一个二分类变量的概率。逻辑回归的基本思想是，将输入特征加权求和，然后通过一个激活函数将加权和映射到一个概率值，这个概率值表示输入特征属于正类的概率。

在训练阶段，逻辑回归算法会通过最大化似然函数来学习模型参数，常用的方法是梯度下降法。

在测试阶段，逻辑回归算法将输入特征代入训练好的模型，得到一个概率值，如果概率大于等于一个阈值，通常是0.5，就将样本预测为正类，否则将样本预测为负类。
