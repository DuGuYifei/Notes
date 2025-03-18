# MobileNet
简介
--

使用了深度卷积 depthwise convolutions，这种卷积方式将标准卷积分为两部分，首先应用深度卷积，然后是逐点卷积 pointwise convolutions，从而减少模型的计算复杂度和参数数量