# 导入cv模块
import cv2 as cv


# 建立检测函数
def face_detect_demo(img):
    # img = cv.resize(img, (960, 540))
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    face_detect = cv.CascadeClassifier('C:\OpenCV\opencv\sources\data\haarcascades\haarcascade_frontalface_default.xml')
    face = face_detect.detectMultiScale(gray, 1.5, 5)
    for f in face:
        cv.rectangle(img, f, (0, 0, 255), 2)
    cv.imshow('result', img)


# 读取摄像头
cap = cv.VideoCapture(0)
# cap = cv.VideoCapture('E:\视频\\test.flv')
"""
等待输入视频的名字 test被我删除了
"""
# 等待
while True:
    flag, frame = cap.read()
    if not flag:
        break
    face_detect_demo(frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
# 释放内存
cv.destroyAllWindows()
# 释放摄像头
cap.release()
