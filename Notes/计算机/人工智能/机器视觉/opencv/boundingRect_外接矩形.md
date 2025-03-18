# boundigRect_外接矩形

## 1. boundingRect函数
```cpp
cv::Rect cv::boundingRect(const std::vector<cv::Point> &points);
```

## 2. 说明

`boundingRect`函数用于计算轮廓的外接矩形。

## 3. 案例

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::vector<cv::Point> contour;
    contour.push_back(cv::Point(0, 0));
    contour.push_back(cv::Point(0, 100));
    contour.push_back(cv::Point(100, 100));
    contour.push_back(cv::Point(100, 0));

    cv::Rect rect = cv::boundingRect(contour);
    std::cout << "Bounding rect: " << rect << std::endl;

    return 0;
}
```