# 形态学运算_morphologyEx

[形态学运算_腐蚀(erode)和膨胀(dilate)](形态学运算_腐蚀(erode)和膨胀(dilate).md)

cv2.morphologyEx(src, op, kernel)

## src
输入图像，即源图像，填Mat类的对象即可；

## kernel
形态学运算的内核。若为NULL时，表示的是默认使用参考点位于中心3 x 3的核。
一般使用函getStructuringElement()配合这个参数的使用。
[getStructuringElement()](getStructuringElement.md)函数会返回指定形状和尺寸的结构元素（内核矩阵）

## op 
高级形态学变换
1. 开运算（Opening operation）：
   - MORPH_OPEN
   - 先腐蚀，再膨胀，可清除一些小东西(亮的)，放大局部低亮度的区域
2. 闭运算（Closing operation）：
   - MORPH_CLOSE
   - 先膨胀，再腐蚀，可清除小黑点
3. 形态学梯度（Morphological gradient）：
   - MORPH_GRADIENT
   - 膨胀图与腐蚀图之差，提取物体边缘
4. 顶帽（“Top hat”）：
   - MORPH_TOPHAT
   - 原图像-开运算图，突出原图像中比周围亮的区域
5. 黑帽（“Black hat”）：
   - MORPH_BLACKHAT
   - 闭运算图-原图像，突出原图像中比周围暗的区域
6.  MORPH_ERODE ：“腐蚀”；
    MORPH_DILATE ：“膨胀”