# Yolo

## 介绍
因为只需要看一次，YOLO被称为Region-free方法，相比于Region-based方法，YOLO不需要提前找到可能存在目标的Region。

也就是说，一个典型的Region-base方法的流程是这样的：先通过计算机图形学（或者深度学习）的方法，对图片进行分析，找出若干个可能存在物体的区域，将这些区域裁剪下来，放入一个图片分类器中，由分类器分类。

## detect
```bash
python detect.py --weights ../valorant-v12.pt --source ../test.mp4 --view-img --save-txt
```

加上`--device 0` 意思是第1个gpu的cuda，但其实如果存在会默认使用

### pytorch 和 cuda
现在pytorch自带了cuda和cudnn的功能，所以大胆点用gpu是真的快！

不用 90ms 一次检测，用了9ms一次检测

## export
[用opencv的dnn模块做yolov5目标检测](https://blog.csdn.net/nihate/article/details/112731327)

1. 一开始export的onnx在c++里用opencv读取总是失败，
2. 然后将conda环境里的pytorch按yolov5文档下载版本，但是要先将conda环境按pytorch官网要求小于等于3.8。
3. 然后发现import onnx出现问题，只需要将onnx包降低版本即可。
4. 此时export出的onnx可以被opencv阅读了。

