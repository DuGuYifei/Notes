# 导入cv模块
import cv2 as cv

# 读取图片
img = cv.imread('face1.jpg')
# 坐标
x, y, w, h = 100, 100, 100, 100
# 绘制矩形
cv.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 1)
cv.rectangle(img, (x, y, 50 + w, 50 + h), (0, 0, 255), 5)
# 绘制圆形
cv.circle(img, (x + w, y + w), 100, (255, 0, 0), 10)
# 显示
cv.imshow('re_img', img)
# 等待
while True:
    if ord('q') == cv.waitKey(0):
        break
# 释放内存
cv.destroyAllWindows()
