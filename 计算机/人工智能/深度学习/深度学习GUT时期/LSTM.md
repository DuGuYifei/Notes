# LSTM
简介
--

是[RNN](RNN.md)变体

*   Has **2** state vectors: _Hidden state_ and _Cell state_
*   Has **3** types of gates: _Input_, _Output_ and _Forget_
*   has **4** times more parameters than Simple RNN (when the vector state has the same length)
*   Typically, for gates implementation neurons with ReLU activation function **is not** used, Use [sigmoid](%E6%BF%80%E6%B4%BB%E5%87%BD%E6%95%B0.md)

梯度爆炸问题
------

[梯度爆炸和梯度裁剪](ExplodingGradient%E5%92%8CGradientClip.md)