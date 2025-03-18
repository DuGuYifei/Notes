# isContourConvex_判断轮廓是否是凸的

## 1. 说明

`isContourConvex`函数用于判断轮廓是否是凸的。

## 2. 函数原型

```cpp
bool cv::isContourConvex(const std::vector<cv::Point> &contour);
```

## 3. 参数

* `contour`：输入的轮廓。
* 返回值：如果轮廓是凸的，则返回 `true`；否则返回 `false`。

## 4. 示例

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::vector<cv::Point> contour;
    contour.push_back(cv::Point(0, 0));
    contour.push_back(cv::Point(0, 100));
    contour.push_back(cv::Point(100, 100));
    contour.push_back(cv::Point(100, 0));

    bool is_convex = cv::isContourConvex(contour);
    std::cout << "Is contour convex? " << is_convex << std::endl;

    return 0;
}
```

## 原理

`isContourConvex`函数的实现原理是通过计算轮廓的凸包（convex hull）来判断轮廓是否是凸的。如果轮廓的凸包与轮廓本身完全一致，则说明轮廓是凸的。

凸包就是将一个形状包裹起来的最小凸多边形。