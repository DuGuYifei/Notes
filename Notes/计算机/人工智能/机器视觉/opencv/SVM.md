# SVM

[OpenCV中的「SVM分类器」：基本原理、函数解析和示例代码_虾米小馄饨的博客-CSDN博客_svm分类器](https://blog.csdn.net/Bit_Coders/article/details/118493604)

[SVM原理](../AI算法/SVM.md)

## 创建
```cpp
Ptr<SVM>svm = SVM::create();
```

## 设置模型类型
```cpp
enum  Types {
  C_SVC =100,//C-支持向量分类。n级分类（n≥ 2) 允许使用异常值的惩罚乘数 C 不完全地分离类。
  NU_SVC =101,//ν-支持向量分类。n级分类，可能有不完美的分离。参数ν用于代替C，参数ν在0-1范围内，值越大，决策边界越平滑。
  ONE_CLASS =102,//分布估计，所有的训练数据都来自同一个类，SVM 构建了一个边界，将类与特征空间的其余部分分开。
  EPS_SVR =103,//ε-支持向量回归。来自训练集的特征向量和拟合超平面之间的距离必须小于p。对于异常值，使用惩罚乘数 C。
  NU_SVR =104 // ν-支持向量回归。 ν用于代替 p。
}
virtual void cv::ml::SVM::setType(int val)
```

## 设置参数C
C值较大时：误分类错误较少，但余量较小。这种情况下，侧重于寻找具有很少的误分类错误的超平面。
C值较小时：具有更大余量和更多分类错误。在这种情况下，更侧重于寻找具有大余量的超平面。

`svm->setC()`后就不能用`trainAuto()`

```cpp
virtual void cv::ml::SVM::setC(double val)
```

## 设置核函数
```cpp
enum KernelTypes {
  CUSTOM =-1,//由SVM::getKernelType返回，默认是RBF
  LINEAR =0,//线性内核，速度最快
  POLY =1,//多项式核
  RBF =2,//径向基函数（RBF），大多数情况下是个不错的选择
  SIGMOID =3,//sigmoid核
  CHI2 =4,//Chi2核，类似于RBF核
  INTER =5//直方图交叉核，速度较快
}
virtual void cv::ml::SVM::setKernel(int kernelType) 
```

## 设置迭代算法的终止标准
```cpp
virtual void cv::ml::SVM::setTermCriteria(const cv::TermCriteria &val)    

// cv::TermCriteria
cv::TermCriteria::TermCriteria (int type,int maxCount,double epsilon)

// Type 
enum  cv::TermCriteria::Type {
  COUNT = 1,
  MAX_ITER = COUNT,//最大迭代次数
  EPS = 2 //迭代算法停止时所需的精度或参数变化
}
```

## 训练SVM模型
`trainAuto`方法通过选择最佳参数 C、gamma、p、nu、coef0、degree 来自动训练 SVM 模型。当测试集误差的交叉验证估计最小时，参数被认为是最佳的。此函数仅使用SVM::getDefaultGrid进行参数优化，因此仅提供基本的参数选项。

`trainAuto`函数适用于分类（SVM::C_SVC或SVM::NU_SVC）以及回归（SVM::EPS_SVR或SVM::NU_SVR）。如果是SVM::ONE_CLASS，则不进行优化，并执行带有 params 中指定参数的常用 SVM。

也可以直接写train()
```cpp
//输入由TrainData::create或TrainData::loadFromCSV构造的训练数据
virtual bool cv::ml::SVM::trainAuto(const Ptr<TrainData> & data,
int     kFold = 10,
ParamGrid     Cgrid = getDefaultGrid(C),
ParamGrid     gammaGrid = getDefaultGrid(GAMMA),
ParamGrid     pGrid = getDefaultGrid(P),
ParamGrid     nuGrid = getDefaultGrid(NU),
ParamGrid     coeffGrid = getDefaultGrid(COEF),
ParamGrid     degreeGrid = getDefaultGrid(DEGREE),
bool     balanced = false 
)    

//输入训练样本
bool cv::ml::SVM::trainAuto(InputArray samples,
    int     layout,
    InputArray     responses,
    int     kFold = 10,
    Ptr< ParamGrid >     Cgrid = SVM::getDefaultGridPtr(SVM::C),
    Ptr< ParamGrid >     gammaGrid = SVM::getDefaultGridPtr(SVM::GAMMA),
    Ptr< ParamGrid >     pGrid = SVM::getDefaultGridPtr(SVM::P),
    Ptr< ParamGrid >     nuGrid = SVM::getDefaultGridPtr(SVM::NU),
    Ptr< ParamGrid >     coeffGrid = SVM::getDefaultGridPtr(SVM::COEF),
    Ptr< ParamGrid >     degreeGrid = SVM::getDefaultGridPtr(SVM::DEGREE),
    bool     balanced = false 
) 
/*
samples：训练样本
layout：参考 ml::SampleTypes，如cv.ml.ROW_SAMPLE表示每个训练样本是行向量，cv.ml.COL_SAMPLE表示每个训练样本是列向量
responses：与训练样本有关的响应向量
kFold：k交叉验证，训练集会分成k个子集，从中选取一个用来测试，剩余k-1个用来训练
balanced：如果设为True且是2-class分类问题，方法会自动创建更平衡的交叉验证子集，即子集中的类之间比例接近整个训练数据集中的比例
*/
```

## 预测结果
```cpp
// 预测输入样本的响应结果
virtual float predict(
  InputArray  samples,                  // input samples, float matrix
  OutputArray results = cv::noArray(),  // optional output results matrix
  int         flags   = 0               // (model-dependent)
) const = 0;
```

`svm->predict(testImg2);` 返回标签值

`svm->predict(testImg2, res)` 返回值没得用，标签在res里，可以通过 `res.at<int>(0,0) == 1` 读出第一个标签


## 误差计算
```cpp
// 在训练集或测试集上计算误差
virtual float calcError(
  const Ptr<TrainData>& data, // training samples
  bool test, // true: compute over test set
      // false: compute over training set
  cv::OutputArray resp  // the optional output responses
) const;
```

## 保存SVM模型
```cpp
void cv::Algorithm::save(const String &filename)  const
```

## 加载SVM
```cpp
static Ptr<SVM> cv::ml::SVM::load(const String &filepath)
```

## 案例1
[（四十四）OpenCV中的机器学习-SVM](https://zhuanlan.zhihu.com/p/92021418)
```cpp
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace cv::ml;

int main(int, char**)
{
    // Set up training data
    //! [setup1]
    int labels[4] = {1, 1, -1, -1};
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    //! [setup1]
    //! [setup2]
    Mat trainingDataMat(4, 2, CV_32F, trainingData);
    Mat labelsMat(4, 1, CV_32SC1, labels);
    //! [setup2]

    // Train the SVM
    //! [init]
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    //! [init]
    //! [train]
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
    //! [train]

    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Show the decision regions given by the SVM
    //! [show]
    Vec3b green(0,255,0), blue(255,0,0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = svm->predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    }
    //! [show]

    // Show the training data
    //! [show_data]
    int thickness = -1;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness );
	circle(image, Point(255, 10), 5, Scalar(0, 0, 0), thickness);
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness );
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness );
    //! [show_data]

    // Show support vectors
    //! [show_vectors]
    thickness = 2;
    Mat sv = svm->getUncompressedSupportVectors();

    for (int i = 0; i < sv.rows; i++)
    {
        const float* v = sv.ptr<float>(i);
        circle(image,  Point( (int) v[0], (int) v[1]), 6, Scalar(0, 0, 255), thickness);
    }
    //! [show_vectors]

    imwrite("result.png", image);        // save the image

    imshow("SVM Simple Example", image); // show it to the user
    waitKey();
    return 0;
}
```

## 案例2
```cpp
void test_svm(std::string videopath, std::string svm_file = "svm.mat")
{
    /// 加载svm模型参数
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::load(svm_file);

    /// 初始化特征提取器
    // 此处省略……
    
    cv::VideoCapture cap(videopath);
    if (cap.isOpened())
    {
        cv::Mat src;//img
        int sleep_interval = 1;//每隔多少ms取帧
        int frameIdx = 0;
        while (true)
        {
            if (!cap.read(src))
            {
                break;
            }
            frameIdx++;

            double start = static_cast<double>(cv::getTickCount());
            cv::Mat flowFeat;
            
            //提取运动特征
            m_featureExtactor.ProcessFlow(src, flowFeat);
            flowFeat.convertTo(flowFeat, CV_32FC1);
            
            //获取分类结果
            int response = (int)svm->predict(flowFeat);
            cv::putText(src, cv::String(std::to_string(response)), cv::Point(20,20), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0));  
            
            //计算耗时
            float times = ((float)cv::getTickCount() - start) / cv::getTickFrequency();
            std::cout << "time cost: " << times << " s." << std::endl;
            cv::imshow("img", src);
            if (cv::waitKey(1) == 27) {
                break;
            }
        }
    }
}
```