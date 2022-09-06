# Mat和numpy的关系以及python屏幕截图并转换成opencv可读的形式

```py
from PIL import ImageGrab
im = ImageGrab.grab(bbox=rect)
img0 = np.array(im)
```
