# findcontours_轮廓查找

```cpp
cv::findCountours(
    InputArray binImg;      //输入图像
    OutputArrayOfArrays contours,   //发现的轮廓对象
    OutputArray hierarchy,//图像的拓扑结构
    int mode,                       //轮廓返回的模式
    int method,                 //发现的方法
    Point offset= Point()   //轮廓像素的位移
)
/*
第⼀个参数：image，单通道图像矩阵，可以是灰度图，但更常⽤的是⼆值图像，⼀般是经过Canny、拉普拉斯等边缘检测算⼦处理过的⼆值图像；

第⼆个参数：contours，定义为“vector<vector<Point>> contours”，是⼀个向量，并且是⼀个双重向量，向量内每个元素保存了⼀组由连续的Point点构成的点的集合的向量，每⼀组Point点集就是⼀个轮廓。有多少轮廓，向量contours就有多少元素。

第三个参数：hierarchy，定义为“vector<Vec4i> hierarchy”，先来看⼀下Vec4i的定义：
typedef Vec<int,4> Vec4i;
Vec4i是Vec的别名，定义了⼀个“向量内每⼀个元素包含了4个int型变量”的向量。所以从定义上看，hierarchy也是⼀个向量，向量内每个元素保存了⼀个包含4个int整型的数组。向量hiararchy内的元素和轮廓向量contours内的元素是⼀⼀对应的，向量的容量相同。
hierarchy向量内每⼀个元素的4个int型变量——hierarchy[i][0] ~hierarchy[i][3]，分别表⽰第i个轮廓的后⼀个轮廓、前⼀个轮廓、第一个内嵌轮廓、父轮廓的索引编号。如果当前轮廓没有对应的后⼀个轮廓、前⼀个轮廓、⽗轮廓或内嵌轮廓的话，则hierarchy[i][0] ~hierarchy[i][3]的相应位被设置为默认值-1。

第四个参数：int型的mode，定义轮廓的检索模式：
取值⼀：CV_RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
取值⼆：CV_RETR_LIST   检测所有的轮廓，包括内围、外围轮廓，但是检测到的轮廓不建⽴等级关系，彼此之间独⽴，没有等级关系，这就意味着这个检索模式下不存在⽗轮廓或内嵌轮廓，所以hierarchy向量内所有元素的第3、第4个分量都会被置为-1
取值三：CV_RETR_CCOMP  检测所有的轮廓，但所有轮廓只建⽴两个等级关系，外围为顶层，若外围内的内围轮廓还包
含了其他的轮廓信息，则内围内的所有轮廓均归属于顶层
取值四：CV_RETR_TREE，检测所有轮廓，所有轮廓建⽴⼀个等级树结构。外层轮廓包含内层轮廓，内层轮廓还可以继续
包含内嵌轮廓。

第五个参数：int型的method，定义轮廓的近似⽅法：
取值⼀：CV_CHAIN_APPROX_NONE 保存物体边界上所有连续的轮廓点到contours向量内
取值⼆：CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存⼊contours向量内，拐点与拐
点之间直线段上的信息点不予保留
取值三和四：CV_CHAIN_APPROX_TC89_L1，CV_CHAIN_APPROX_TC89_KCOS使⽤teh-Chinl chain 近似算法
*/


//-------------------------------------------------------------
cv:drawContours(
    InputOutputArray binImg;    //输入图像
    OutputArrayOfArrays contours,   //轮廓对象
    Int contourIdx,                     //轮廓索引号
    const Scalar & color,  //绘制的颜色 Scalar color(rand() & 255, rand() & 255, rand() & 255);
    int thickness,                      //绘制线宽
    int lineType,                           //绘制线性
    InputArray hierarchy,           //拓扑结构图
    int maxlevel,                       //最大层数，0为只绘制当前的，1为绘制当前及内嵌的轮廓
    Point offset = Point()          //轮廓位移
)
```

* 如果drawcontour没有彩色其实是因为图片是单通道，要先转为三通道（最开始时候直接保留一份原图就好）,如下：
```cpp
    VideoCapture cap("../testRed.avi");
	Mat video1, video2;
	Mat bgrChannels[3];

	while (true)
	{
		cap >> video1;
		video2 = video1.clone();
		split(video1, bgrChannels);//分离通道
		
		//二值化（红色光用 2-0， 蓝色光用 0-2，为了保证正值）
		//结果输出回video1
		threshold(bgrChannels[2] - bgrChannels[0], video1, 100, 255, CV_THRESH_BINARY_INV);


		//轮廓
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(video1, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		Scalar color(255,0,0);
		drawContours(video2, contours, 0, color, CV_FILLED, 8);
		imshow("frame", video1);


		//让程序等待1ms 不然太快了不显示
		waitKey(1);
```

* 如果参数无法使用，如下
  
  | 关键字      | 所包含头文件                             |
  | ----------- | ---------------------------------------- |
  | CV_RGB2GRAY | `#include<opencv2/imgproc/types_c.h>`    |
  | CV_MINMAX   | `#include<opencv2/opencv.hpp>`           |
  | CV_RGB2GRAY | `#include <opencv2/highgui/highgui_c.h>` |
  | CV_FILLED   | #include <opencv2/imgproc/imgproc_c.h>   |
## 原理
[图像边缘Canny算子提取_AnimateX的博客-CSDN博客_canny算子阈值怎么取](https://blog.csdn.net/animatex/article/details/79983020)