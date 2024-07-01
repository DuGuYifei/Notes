# Lecture 11 - RNNs and Transformers

## Transfer Learning 迁移学习

老师PS:主要谈论的是基于ImageNet的预训练模型，如何迁移到其他任务上。CV的大部分工作都是用的这种方法，利用pre-trained的模型来做downstream(下游)的任务。

* 训练模型可能会因为限制的数据和其他资源而变得困难，比如标注数据，所以考虑重用pre-trained模型。
* 有时候这种操作被称为**fine-tuning**，但是这个词有点误导，因为我们可能会改变模型的一些部分，而不仅仅是调整参数。
* ![alt text](_attachments/Lecture11-RNNsAndTransformers/image.png)
* 如果数据集足够大，可以**用较小的学习率train更多的层**，frozen更少的层
  * 也可以靠近原始图的层用较小的学习率，远离原始图的层用较大的学习率（理解，小的学习率保护了原本的特征提取）
* 什么时候使用：
  * Task T1和T2的输入相同（比如都是RGB图像）
  * T1的数据集比T2大
  * 当T1的low-level features对T2有帮助时
* 老师PS: 具体的实例，比如stable diffusions，即便是大公司更多的也是fine-tuning，而不是从头训练。

## Representation Learning 表征学习

老师PS: 和transfer learning一个思路，先学习一个好的表征，然后再做downstream的任务。 

* 什么是好的特征：
  * good features are essential for successful machine learning
  * (Supervised) deep learning 基于使用的练数据: input/target labels
  * 输入的变化(noise，irregularities(不规则), etc. )可能导致截然不同的结果
* 表征学习：
  * 允许发现被不同的任务所需要的特征
  * 深度表征学习：模型将 input X map 到输出 Y。
  * 直觉的，深度网络会学习不同层级的abstraction(抽象)。e.g. low-level->mid-level->high-level
    * 理解：而这些抽象又没有label
* 如何学习到好的特征：
  * determine desired feature invariances (翻译：确定所需的特征不变性)
    * 理解：e.g. translation invariance(平移不变性), rotation invariance(旋转不变性), scale invariance(尺度不变性)
    * 理解：所以可以通过augmentation(数据增强)来实现这些不变性
  * 因此教机器来区分相似和不想死的东西
    * 即：**self-supervised learning** 自监督学习

### 自监督学习和对比学习和表征学习

* **对比学习是自监督学习的一种形式，对比学习是表征学习的一种方法。但是表征学习可以是监督的、无监督的、自监督的。**
* 自监督学习常常包括比如：预测任务（预测未来的数据点、缺失的部分或序列的下一个元素等），自编码器，以及对比学习。
* 对比学习专注于通过比较样本对来学习特征表示。在对比学习中，模型学习区分**相似（positive）样本对和不相似（negative）样本**对，目的是使相似样本的表示更接近，而不相似样本的表示更远离。
* 对比学习主要用于语音识别、CV等领域。

对比学习：
* 有很多种方式，比如：**Siamese Networks**, Triplet Networks, SimCLR, MoCo, SwAV, BYOL, PIRL, etc.

#### Siamese Networks 孪生网络

PS: Siamese 暹罗，泰国的古称，后来因为一对叫Eng & Chang Bunker的连体双胞胎（后为马戏团成员）而带有了“孪生，连体”的意思。

![alt text](_attachments/Lecture11-RNNsAndTransformers/image-1.png)

![alt text](_attachments/Lecture11-RNNsAndTransformers/image-2.png)

通过对两个图像已知是否是同一个图来训练，并使得loss function来比较相似，使loss最小，相似最大。

GPT重点：两个encoder不是说真的两个encoder，其实就是并行的概念，这是两个一摸一样的网络，共享参数，只是并行来处理两个不同的输入，最后通过常见的度量方式包括欧氏距离、余弦相似性等来比较是否相似。可应用于：人脸验证，签名识别，异常检测，匹配和分类等。

对于上图中出现了fine tuning，理解见下一小节。

## 个人理解-迁移学习和表征学习

* 表征学习其可以作为迁移学习的前一步，好的表征学习可以更好的用于迁移学习。
* 但是表征学习，比如对比学习里的孪生网络，其实本身也可以有一些实际用途，但是也可以将encoder部分拿出来用作迁移学习来识别具体的东西，因为它提取了好的特征。

