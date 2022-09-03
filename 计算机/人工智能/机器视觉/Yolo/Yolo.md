# Yolo

## 介绍
因为只需要看一次，YOLO被称为Region-free方法，相比于Region-based方法，YOLO不需要提前找到可能存在目标的Region。

也就是说，一个典型的Region-base方法的流程是这样的：先通过计算机图形学（或者深度学习）的方法，对图片进行分析，找出若干个可能存在物体的区域，将这些区域裁剪下来，放入一个图片分类器中，由分类器分类。

## detect
```bash
detect.py --weights ../valorant-v12.pt --source ../test.mp4 --view-img --save-txt
```

## export
[用opencv的dnn模块做yolov5目标检测](https://blog.csdn.net/nihate/article/details/112731327)

