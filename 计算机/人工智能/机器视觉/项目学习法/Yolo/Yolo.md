# Yolo

## 介绍
因为只需要看一次，YOLO被称为Region-free方法，相比于Region-based方法，YOLO不需要提前找到可能存在目标的Region。

也就是说，一个典型的Region-base方法的流程是这样的：先通过计算机图形学（或者深度学习）的方法，对图片进行分析，找出若干个可能存在物体的区域，将这些区域裁剪下来，放入一个图片分类器中，由分类器分类。

## detect
```bash
python detect.py --weights ../valorant-v12.pt --source ../test.mp4 --view-img --save-txt
```
### detect关键函数提取以自使用测试
[yolov5_valorant项目网址](https://github.com/DuGuYifei/Yolov5_FPS_AICheatPrinciple)
```py
import win32api
import win32con
from PIL import ImageGrab
import numpy as np
import torch
import cv2

from utils.augmentations import letterbox
from utils.general import (non_max_suppression, scale_coords)
from models.experimental import attempt_load

# pt_path = 'valorant-v12.pt'
pt_path = 'valorant-bot.pt'

def run():
    rect = (0, 0, 1920, 1080)
    mid_screen_x = (rect[2] - rect[0]) >> 1
    mid_screen_y = (rect[3] - rect[1]) >> 1
    mid_screen = mid_screen_x + mid_screen_y
    aims = []
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    half = device != 'cpu'
    conf_thres = 0.4
    iou_thres = 0.05

    model = attempt_load(pt_path, device=device, inplace=True, fuse=True)
    stride = max(int(model.stride.max()), 32)  # model stride
    model.half()

    open_helper = False

    while True:
        if ((win32api.GetAsyncKeyState(0x01) & 0x8000) > 0 or (
                win32api.GetAsyncKeyState(0x02) & 0x8000) > 0) and open_helper:
            im = ImageGrab.grab(bbox=rect)
            img0 = np.array(im)
            img = letterbox(img0, stride=stride)[0]
            img = np.ascontiguousarray(img)
            img = torch.from_numpy(img).to(device)
            img = img.half() if half else img.float()
            img /= 255  # 0 - 255 to 0.0 - 1.0
            if len(img.shape) == 3:
                img = img[None]  # 压缩数据维度

            img = img.permute(0, 3, 1, 2)
            pred = model(img, augment=False, visualize=False)[0]
            pred = non_max_suppression(pred, conf_thres, iou_thres)

            # Process predictions (based on source code of yolo)
            for i, det in enumerate(pred):  # per image
                if len(det):
                    # Rescale boxes from img_size to im0 size
                    det[:, :4] = scale_coords(img.shape[2:], det[:, :4], img0.shape).round()
                    # Write results
                    for *xyxy, conf, cls in reversed(det):
                        aims.append(((xyxy[0] + xyxy[2]) / 2, (xyxy[3] - xyxy[1]) / 5 + xyxy[1]))

                if len(aims):
                    min_dis = 100000
                    target_x = 960
                    target_y = 540
                    for a, b in aims:
                        dis = a + b - mid_screen
                        if dis < min_dis:
                            target_x = a
                            target_y = b
                            min_dis = dis
                    print(f"{target_x}, {target_y}")
                    aims = []

if __name__ == "__main__":
    run()
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

## 项目
* [GitHub - DuGuYifei/Yolov5_FPS_AICheatPrinciple: The AI cheating principle of fps game. (This is only used for learning)](https://github.com/DuGuYifei/Yolov5_FPS_AICheatPrinciple)
* [Research AI used in shooting game, but sadly it need be private repo. Otherwise many people will use it. ](https://github.com/DuGuYifei/AI_ShootingGame)