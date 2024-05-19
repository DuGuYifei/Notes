# threshold和adaptiveThreshold

## 介绍
1. cv::threshold:
   1. [threshold_二值化](threshold_二值化.md)
   2. 这是一种简单的阈值处理方法，它涉及到一个全局阈值。如果像素值高于（或低于，取决于阈值类型）设定的阈值，则将这个像素值设置为最大值（通常是255），否则设置为0。
   3. 主要用于图像相对均匀，或者当整个图像上的光照分布较为一致时。
   4. 该方法包括几种不同的阈值类型，例如：二进制阈值（THRESH_BINARY）、反二进制阈值（THRESH_BINARY_INV）、截断阈值（THRESH_TRUNC）、阈值化到零（THRESH_TOZERO）及其反转（THRESH_TOZERO_INV）等。
2. cv::adaptiveThreshold:
   1. 这是一种更复杂的阈值处理方法，它不使用全局常数阈值。而是为图像的每个小区域计算不同的阈值，这样可以根据图像在该区域的特性自适应地改变阈值。
   2. cv::adaptiveThreshold 特别适用于图像在不同区域具有不同光照条件的情况。它可以帮助在光照变化的区域内更好地保持细节。
   3. 该方法通常使用方法如均值适应性阈值（ADAPTIVE_THRESH_MEAN_C）和高斯适应性阈值（ADAPTIVE_THRESH_GAUSSIAN_C）。

## 参数介绍

### cv::threshold
```cpp
void cv::threshold(
    InputArray src, // 输入图像
    OutputArray dst, // 输出图像
    double thresh, // 阈值
    double maxval, // 最大值
    int type // 阈值类型
);
```

### cv::adaptiveThreshold
```cpp
void cv::adaptiveThreshold(
    InputArray src, // 输入图像
    OutputArray dst, // 输出图像
    double maxValue, // 最大值
    int adaptiveMethod, // 自适应方法
    int thresholdType, // 阈值类型
    int blockSize, // 区域大小
    double C // 常数
);
```

### 具体参数

1. 阈值类型：
   1. THRESH_BINARY: $dst(x, y) = \begin{cases} maxval & \text{if } src(x, y) > thresh \\ 0 & \text{otherwise} \end{cases}$
   2. THRESH_BINARY_INV: $dst(x, y) = \begin{cases} 0 & \text{if } src(x, y) > thresh \\ maxval & \text{otherwise} \end{cases}$
   3. THRESH_TRUNC: $dst(x, y) = \begin{cases} thresh & \text{if } src(x, y) > thresh \\ src(x, y) & \text{otherwise} \end{cases}$
   4. THRESH_TOZERO: $dst(x, y) = \begin{cases} src(x, y) & \text{if } src(x, y) > thresh \\ 0 & \text{otherwise} \end{cases}$
   5. THRESH_TOZERO_INV: $dst(x, y) = \begin{cases} 0 & \text{if } src(x, y) > thresh \\ src(x, y) & \text{otherwise} \end{cases}$
   6. ADAPTIVE_THRESH_MEAN_C: $T(x, y) = \text{mean}(x, y) - C$
   7. ADAPTIVE_THRESH_GAUSSIAN_C: $T(x, y) = \text{mean}(x, y) - C$
2. 区域大小：指的是计算阈值时使用的像素邻域大小，一般为奇数（因为是以当前像素为中心），它决定了图像的分块大小。为什么需要分域呢，因为在不同区域内的光照条件可能不同，所以需要不同的阈值。

