# 导入cv模块
import cv2 as cv


# 建立检测函数
def face_detect_demo():
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    face_detect = cv.CascadeClassifier('C:\OpenCV\opencv\sources\data\haarcascades\haarcascade_frontalface_alt2.xml')
    face = face_detect.detectMultiScale(gray, 1.1, 1, 0, (10, 10), (300, 300))
    for f in face:
        cv.rectangle(img, f, (0, 0, 255), 2)
    cv.imshow('result', img)


# 读取图片
img = cv.imread('face2.png')

# 检测函数
face_detect_demo()

# 等待
while True:
    if ord('q') == cv.waitKey(0):
        break
# 释放内存
cv.destroyAllWindows()
