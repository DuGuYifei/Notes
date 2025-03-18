# Mat

## clone, copyto, =
`=` 浅拷贝

`clone()` 深拷贝

`copyto()` 如果被赋值的对象要重新申请空则是深拷贝，否则浅拷贝

```cpp
Mat A  = Mat::ones(4,5,CV_32F);

Mat B = A.clone()    //clone 是完全的深拷贝，在内存中申请新的空间，与Ａ独立

Ｍat C;

//此处的Ｃ矩阵大小与Ａ大小不一致，则申请新的内存空间，并完成拷贝，等同于clone()
A.copyTo(C) 

Mat D = A.col(１);

//--------------------------------
//此处D矩阵大小与Ａ.col(0)大小一致，因此不会申请空间，既然不申请空间，
// 那么Mat D = A.col(１);的等号=就说明，A改变了会影响D的值。
//而是直接进行拷贝，相当于把Ａ的第0列赋值给第1列
A.col(0).copyTo(D)
```


## 创建
```cpp
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    Mat trainingDataMat(4, 2, CV_32F, trainingData);
```

## push_back
```cpp
	Mat image[4];
	threshold(imread("../target1.jpg"), image[0],122,1, THRESH_BINARY);
	threshold(imread("../target1.jpg"), image[1],122,1, THRESH_BINARY);
	threshold(imread("../target1.jpg"), image[2],122,1, THRESH_BINARY);
	threshold(imread("../target1.jpg"), image[3],122,1, THRESH_BINARY);
	image[0] = image[0].reshape(0, 1);
	image[1] = image[1].reshape(0, 1);
	image[2] = image[2].reshape(0, 1);
	image[3] = image[3].reshape(0, 1);
	Mat trainData;
	trainData.push_back(image[0]);
	trainData.push_back(image[1]);
	trainData.push_back(image[2]);
	trainData.push_back(image[3]);
```

## 读取

1. at
   `res.at<int>(0,0) == 1`