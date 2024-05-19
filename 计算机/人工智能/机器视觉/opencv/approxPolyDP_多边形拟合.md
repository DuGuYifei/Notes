# approxPolyDP_多边形拟合

## 1. 原理

`cv::approxPolyDP` 是 OpenCV 中的一个多边形拟合函数，它的原理是：给定一个曲线，`cv::approxPolyDP` 函数可以用更少的点来近似表示这个曲线。它的实现原理是：首先将曲线用直线段连接起来，然后根据给定的精度 `epsilon` 来逐步减少直线段的数量，直到满足精度要求。这样就得到了一个多边形。

## 2. 函数原型
`cv::approxPolyDP` 是 OpenCV 中的一个多边形拟合函数，它的原型如下：

```cpp
void cv::approxPolyDP(
    InputArray curve, // 输入曲线
    OutputArray approxCurve, // 输出曲线
    double epsilon, // 精度
    bool closed // 是否闭合
);
```

## 3. 参数解释

epsilon：精度，即拟合的精度。当 epsilon 越小，拟合的精度越高，拟合的点越多；当 epsilon 越大，拟合的精度越低，拟合的点越少。精度的计算方式是：曲线到拟合多边形的最大距离，这个距离可以用[Ramer-Douglas-Peucker算法](../../../计算机图形学/计算机图形学知识积累/Ramer-Douglas-Peucker算法.md) 来理解。

比如我们可以尝试结合`cv::arcLength`函数来计算曲线的周长，然后设置 epsilon 为周长的百分比。

## 4. 案例

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat img = cv::imread("test.jpg");
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, gray, 100, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat dst = cv::Mat::zeros(img.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++) {
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contours[i], approx, 10, true);
        cv::drawContours(dst, {approx}, -1, cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("dst", dst);
    cv::waitKey(0);
    return 0;
}
```