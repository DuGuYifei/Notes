# Scalar_三四元组可选

```cpp
Scalar(double v0, double v1 = 0, double v2 = 0, double v3 = 0);
```

创建一个 Scalar 对象，并用指定的值初始化各个分量。

* v0：第一个分量值，通常表示蓝色（在 BGR 颜色空间中）。
* v1：第二个分量值，通常表示绿色（在 BGR 颜色空间中）。
* v2：第三个分量值，通常表示红色（在 BGR 颜色空间中）。
* v3：第四个分量值（可选），通常用于透明度或其他用途。

```cpp
cv::Scalar blue(255, 0, 0);  // 蓝色 (B, G, R)
cv::Scalar green(0, 255, 0); // 绿色 (B, G, R)
cv::Scalar red(0, 0, 255);   // 红色 (B, G, R)
```