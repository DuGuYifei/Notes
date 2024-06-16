# Lecture 09 - Convolutional Neural Networks

- [FC](#fc)
- [Convolutions](#convolutions)
  - [什么是卷积](#什么是卷积)
    - [对于CNN的作用-自我理解](#对于cnn的作用-自我理解)
    - [计算式边缘处理](#计算式边缘处理)
  - [一个卷积核](#一个卷积核)
  - [多个卷积核 - 卷积层](#多个卷积核---卷积层)
  - [参数和小结](#参数和小结)
  - [不同的Filter](#不同的filter)
  - [Dimensions](#dimensions)
  - [Shape of Weights Tensor](#shape-of-weights-tensor)
- [Pooling](#pooling)
  - [介绍](#介绍)
  - [Max Pooling](#max-pooling)
  - [Average Pooling](#average-pooling)
  - [其他Pooling](#其他pooling)
  - [Dimensions](#dimensions-1)
- [CNN](#cnn)
  - [激活函数问题](#激活函数问题)
  - [多层卷积后的效果](#多层卷积后的效果)
  - [CNN Prototype](#cnn-prototype)
- [Convolutional vs Fully Connected](#convolutional-vs-fully-connected)
- [Receptive field (感受野)](#receptive-field-感受野)


## FC

Fully connected layers 就是每个神经元都和上一层的所有神经元相连，有时候叫MLP（Multi-Layer Perceptron）。

理解：其实前面学的那些基础- 'ordinary' neural network -就都是FC。

Problem:
- 我们不能让网络arbitrarily complex(任意复杂)
- 为什么不just go deeper and get better?
  - No structure
  - It is just brute force
  - Optimization becomes hard
  - Perfoamance plateaus/drop 停滞/下降

Better way than FC:
1. 我们想要限制degrees of freedom
   1. A layer with structure
   2. Weight sharing -> using the same weights for different parts of the input(image)
      1. 意思是：可以用一个通用的filter来获取图片不同部分的特征。

## Convolutions

PS: 数学上 Convolution: 将两个函数(或信号)合并成一个新的函数。

### 什么是卷积

PS: 使用点积来计算卷积，其实矩阵的点积就是[Hadamard乘积](../../../../其他学科知识积累/Maths/Hadamard积.md)，即对应位置相乘。乘完后再求和。

$$f*g = \int_{-\infty}^{\infty} f(\tau)g(t-\tau)d\tau$$

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/recording.gif)


理解：

1. 卷积操作本质上是通过滑动一个函数（通常称为卷积核或滤波器）相对于另一个函数，并在每个滑动位置计算两个函数的重合区域的每一个点的g和f的乘积。
   1. 滑动的是卷积核：将卷积核g从左向右滑动过另一个函数f。
   2. 计算重合部分每个点的乘积：在t时刻计算乘积。
2. 形成了一个关于t的新函数。
3. 意义：量化在每个可能的 t 下 g 对 f 的“贡献”或“影响”
4. 由于原始函数的形状和特性，卷积的结果会展现出某些特定的特征，这些特征反映了两个函数的相互作用方式。例如：
   1. 若两个函数都是方框函数，则卷积结果呈现梯形。
   2. 若两个函数都是高斯函数，则卷积结果仍然是高斯函数，但其标准差不同。
   3. 因此在CNN中可以特征提取，创建复杂模式的层级（从简单特征到复杂特征形成一个层级结构）。当然大多数情况下CNN里都是离散卷积。
   4. ![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-1.png)
   5. ![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-2.png)
5. 上面gif图里的绿色线就是形成的新函数，即f被g卷积后的结果。

#### 对于CNN的作用-自我理解

1. 提取特征
2. 可以减少参数量，否则一张图有太多的像素，参数量会很大

#### 计算式边缘处理

1. Option 1: shrink，即不处理边缘，直接忽略。
2. Option 2（通常）: zero-padding，即在边缘填充0。

### 一个卷积核

5*5*3的卷积核，32*32*3的RGB图片，那么生成的就是28*28*1的feature map / activation map（假设没有padding）。计算方式是将对应的层的像素点与卷积核的对应位置的像素点相乘，然后求和。

### 多个卷积核 - 卷积层

同时使用多个卷积核即可。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-3.png)

### 参数和小结

1. 一次卷积层的参数量由Filter决定 = 卷积核宽 * 卷积核高 * 通道数 (由输入决定) * 卷积核个数 + 卷积核个数（bias）
   1. 通道数：输入的图片的通道数
   2. 卷积核个数：输出的feature map的个数
   3. 为什么要加卷积核个数：每个卷积核都有一个bias。
2. 每个filter提取一个不同的图片特征
3. 不要忘了和Batch norm一样，弄完还得Backpropagation。

### 不同的Filter

--------------------------------

不重要，但是可以了解一下。

常见的特征提取的filter:

* Horizontal edge
* Vertical edge
* Circle
* Square
* ...

所以其实我们并不需要在深度学习手动创建新的filter，都是通过训练得到的，上面提到的其实都是过去用在比如Sobel边缘检测或者其他滤波器里的filter。

--------------------------------

### Dimensions

w/o padding:
1. Input: N * N
2. Filter: F * F
3. Stride: S
4. Output: $(\frac{N-F}{S}+1) * (\frac{N-F}{S}+1)$

Note: 
1. 如果N-F不能被S整除，那么就要考虑padding的问题，否则就是illegal。
2. Filter的个数会是下一个层的通道数。[参数和小结](#参数和小结)

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-5.png)

上图不是一个Good Idea，偶尔才是，因为shrink太快了。所以一般都要用padding，这样就可以获得图片边缘的像素点作为被卷积的对象中心。正常情况都用0填充。

w/ padding:
1. Input: N * N
2. Filter: F * F
3. Stride: S
4. Padding: P
5. Output: $(\frac{N+2P-F}{S}+1) * (\frac{N+2P-F}{S}+1)$ 

叫法：
* Valid Convolution: 
  * no padding
* Same Convolution: 
  * output size = input size
  * Set padding to P = $\frac{F-1}{2}$

### Shape of Weights Tensor

shape是(C, K, F, F)，其中：
* C: 输入的通道数
* K: 输出的通道数, 即filter的个数
* F: filter的宽和高

当然这里省略了bias，所以实际上是(C, K, F, F) + (K, )。

Note: 在不同的资料下，这个也不是绝对的，有时候是：
1. (K, C, F, F)
2. (F, F, C, K)

## Pooling

### 介绍

在CNN里，我们已经知道了经过stride, padding可以调整尺寸，但是我们可以直接通过一个layer来改变size，resolution。

1. **这个层是没有要学习的参数的**。
2. 理解：
   1. Conv Layer = Feature extraction: 计算一个给定区域的特征
   2. Pooling Layer = Feature selection: 选择一个区域的最强（或平均）的activation

### Max Pooling

Filter: 2 * 2, Stride: 2
Output: 在每个2 * 2的区域里取最大值。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-4.png)

### Average Pooling

典型地用在网络的更深层。所以大多数人可能会用Max Pooling多数时候。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-7.png)

### 其他Pooling

1. Min Pooling
2. L2-norm Pooling
3. ...

### Dimensions

* Input volumn of size: $W_{in} * H_{in} * D_{in}$
* Filter Hyperparameters:
  * Filter size: F
  * Stride: S
  * 这里没有Filter Count K, 也没有padding P
* Output volume of size: $W_{out} * H_{out} * D_{out}$
  * $W_{out} = \frac{W_{in} - F}{S} + 1$
  * $H_{out} = \frac{H_{in} - F}{S} + 1$
  * $D_{out} = D_{in}$
* 没有要学习的参数的，是一个fixed function。

## CNN

--------------------------------

不重要，但是可以了解一下。

CNNs can be used in CV:
- single object:
  - Classification
  - Classification + Localization
- Multiple objects:
  - Object Detection
  - Instance segmentation: 识别出图片中的每个instance，然后对每个instance进行segmentation(分割)。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image.png)

--------------------------------

### 激活函数问题

注意下图，CNN的结构里，经过卷积计算后还要经过一个non-linear activation function。即: Conv + ReLU。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-5.png)

### 多层卷积后的效果

有趣的是越深，提取的特征越concrete。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-6.png)

### CNN Prototype

PS: 

1. 要谨慎Min Pooling和ReLU同时使用，因为ReLU是挑选最大值，Min Pooling是挑选最小值。
2. 注意prototye最后**典型的会有有一个或两个FC层**，这个FC层是用来拿卷积提取的特征做最后决定的。
3. 到最后的FC层时候，其实feature map一般都会很小的尺寸，但是很大的深度，比如32*32*64。
4. 然后FC层通向一个比如softmax之类的分类器或者Loss function。
5. 如果最后FC时候参数比整个网络的参数还多，那么就是不理想的，因为你更想提取特征。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-8.png)

## Convolutional vs Fully Connected

1. 我们想要限制degrees of freedom
   1. FC somewhat brute force
   2. Convolutions are structured
2. Sliding window 来使用相同的filter params来提取特征
   1. weight sharing的概念
   2. 不同的location提取相同的特征

## Receptive field (感受野)

**前言-老师讲解**：你希望有一个大的感受野，以便更好地做出决策或计算特征，你想要覆盖尽可能多的像素。这就是为什么你想要一个更大的filter。当然，特别的大的filter意味着更多的参数，也就不太好了，所以你需要权衡。然后有如下设计选择：
1. 使用更大的filter kernel
2. 使用更小的filter kernel，但是通过多层来增加感受野

理解：想象极端情况，filter的size和input的size一样，那么其实传给激活函数的就是经过一次计算得到的整张图的一个特征值。

* Spatial extent of the connectivity of a convolutional filter (翻译：卷积滤波器的连接的空间范围)

其实很简单：

1. 一层layer如下，就是一个像素点对应9个像素点的感受野。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-9.png)

2. 两层layer时候，就是一个像素点对应25个像素点的感受野。

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-10.png)

![alt text](_attachments/Lecture09-ConvolutionalNeuralNetworks/image-11.png)