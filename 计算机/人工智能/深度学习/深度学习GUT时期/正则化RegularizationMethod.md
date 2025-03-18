# 正则化RegularizationMethod
简介
--

1.  multi-task learning
2.  early stopping
3.  Augmentation
    1.  label preserving：图像的旋转，缩放，颜色调整，水平翻转等操作，不改变原类别标签。
    2.  label smoothing：标签可能略微接近于目标标签，比如原0和1，现0.9和0.1
        1.  label changing：变换可能导致图像的原标签不再可以使用
4.  weight decay 权重衰减
    1.  popular norm penalties [L1 L2范数](L1L2%E8%8C%83%E6%95%B0.md)
5.  ensemble methods 集成方法 
    1.  bagging 自举汇聚法
6.  [Dropout](Dropout%E9%9A%8F%E6%9C%BA%E5%A4%B1%E6%B4%BB.md)