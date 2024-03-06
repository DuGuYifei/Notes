## 简介

Faster RCNN - [https://arxiv.org/abs/1506.01497](https://arxiv.org/abs/1506.01497)

Faster R-CNN是截止目前，RCNN系列算法的最杰出产物，two-stage中最为经典的物体检测算法。

1. 推理第一阶段先找出图片中待检测物体的anchor矩形框（对背景、待检测物体进行二分类）
2. 第二阶段对anchor框内待检测物体进行分类

第一阶段就是 RPN (Region Proposal Network)

第二阶段就是 Softmax，生成概率分布

## 对比 R-CNN 和 Fast RCNN

1. RCNN = SS(selective search + SVM)
2. Fast RCNN = SS + Softmax
3. Faster RCNN = RPN + Softmax