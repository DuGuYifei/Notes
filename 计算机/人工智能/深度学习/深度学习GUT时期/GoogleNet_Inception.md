# GoogleNet_Inception
简介
--

GoogleNet（也称为Inception模型）引入多个softmax输出层，用于辅助训练。

1.  Convolutions with 1x1 filters
    1.  reduce the number of feature maps
    2.  act as further filters for optimization
2.  Inception module allows filters of different sizes to be used on the same input images
    1.  It also allows you to "voluntarily" use a simplified map after max-pooling