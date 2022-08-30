# 透视变换_getPerspectiveTransform_warpPerspective

```cpp
CV_EXPORTS Mat getPerspectiveTransform(const Point2f src[], const Point2f dst[], int solveMethod = DECOMP_LU);

/*
@param src input image.
@param dst output image that has the size dsize and the same type as src .
@param M \f$3\times 3\f$ transformation matrix.
@param dsize size of the output image.
@param flags combination of interpolation methods (#INTER_LINEAR or #INTER_NEAREST) and the
optional flag #WARP_INVERSE_MAP, that sets M as the inverse transformation (
\f$\texttt{dst}\rightarrow\texttt{src}\f$ ).
@param borderMode pixel extrapolation method (#BORDER_CONSTANT or #BORDER_REPLICATE).
@param borderValue value used in case of a constant border; by default, it equals 0.

@sa  warpAffine, resize, remap, getRectSubPix, perspectiveTransform
 */
CV_EXPORTS_W void warpPerspective( InputArray src, OutputArray dst,
                                   InputArray M, Size dsize,
                                   int flags = INTER_LINEAR,
                                   int borderMode = BORDER_CONSTANT,
                                   const Scalar& borderValue = Scalar());
```


## 例子
```cpp
// 将矩阵转正（用了透视变换函数）
//目标矩阵
Point2f dstRect[4]{ Point2f(0,0), Point2f(0,height),Point2f(width,height), Point2f(width,0) };
//获得透视变换矩阵
Mat transform = getPerspectiveTransform(rect_point, dstRect);
//开始变换
Mat testImg;
Size2d size{width, height};
warpPerspective(video1, testImg, transform, size);
```