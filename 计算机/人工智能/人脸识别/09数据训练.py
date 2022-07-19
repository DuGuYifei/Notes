import os
import cv2
from PIL import Image
import numpy as np


def get_image_and_labels():
    # 存储人脸数据
    faces_samples = []
    # 存储姓名数据
    ids = []
    # 存储图片信息
    image_paths = [os.path.join(path, f) for f in os.listdir(path)]
    # 加载分类器
    face_detector = cv2.CascadeClassifier('C:\OpenCV\opencv\sources\data\haarcascades\haarcascade_frontalface_alt2.xml')
    # 遍历列表中的图片
    for imagePath in image_paths:
        # 打开图片，灰度化
        # PIL有九种不同的模式：1，L，P，RGB，RGBA，CMYK，YCbCr，I，F。
        # 1 是黑白
        # 2 是灰度
        pil_img = Image.open(imagePath).convert('L')
        # 将图像转化为子数组，以黑白深浅
        img_numpy = np.array(pil_img, 'uint8')
        # 获取图片人脸特征
        faces = face_detector.detectMultiScale(img_numpy)
        # 获取每张图片的id和姓名
        id_img = int(os.path.split(imagePath)[1].split('.')[0])
        # 预防无面容照片
        # 其实这里就是把脸的那一矩阵的数据收入face_samples
        for x, y, w, h in faces:
            ids.append(id_img)
            faces_samples.append(img_numpy[y:y + h, x:x + w])
        # 打印脸部特征和id
        print('id_img:', id_img)
        print('fs:', faces_samples)

    return faces_samples, ids


if __name__ == '__main__':
    # 图片路径
    path = './data'
    # 获取图像数组和id标签数组和姓名
    facesOut, idsOut = get_image_and_labels()
    # 加载识别器
    recognizer = cv2.face.LBPHFaceRecognizer_create()
    # 训练
    recognizer.train(facesOut, np.array(idsOut))
    # 保存文件
    recognizer.write('trainer/trainer.yml')
