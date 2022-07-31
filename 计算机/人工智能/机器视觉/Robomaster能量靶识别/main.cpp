#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
using namespace ml;

constexpr int size_X = 74;
constexpr int size_Y = 35;
constexpr int sampleSize_pos = 15;
constexpr int sampleSize_neg = 15;

void Push_Img(cv::String& filename, Mat& tar)
{
	Mat temp;
	threshold(imread(filename), temp, 122, 1, THRESH_BINARY);
	resize(temp, temp, Size(size_X, size_Y));
	Mat channels[3];
	split(temp, channels);
	tar.push_back(channels[0].reshape(1, 1));
}

void SVM_Train()
{
	Ptr<SVM>svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 1000, FLT_EPSILON));
	svm->setC(10);
	Mat trainData;
	//cv::String f = "../target1.jpg";
	//Push_Img(f, trainData);
	//f = "../target2.jpg";
	//Push_Img(f, trainData);
	//f = "../target5.jpg";
	//Push_Img(f, trainData);
	//f = "../target7.jpg";
	//Push_Img(f, trainData);
	//f = "../target3.jpg";
	//Push_Img(f, trainData);
	//f = "../target4.jpg";
	//Push_Img(f, trainData);
	//f = "../target6.jpg";
	//Push_Img(f, trainData);
	//f = "../target8.jpg";
	//Push_Img(f, trainData);
	
	for (int i = 1; i < sampleSize_pos + sampleSize_neg + 1; i++)
	{
		cv::String f = "test" + to_string(i) + ".png";
		Push_Img(f, trainData);
	}

	//cout << trainData.row(1);			
	trainData.convertTo(trainData, CV_32F);

	Mat label(sampleSize_pos + sampleSize_neg, 1, CV_32S);
	label.rowRange(0, sampleSize_pos).setTo(1);  // Class 1
	label.rowRange(sampleSize_pos, sampleSize_pos + sampleSize_neg).setTo(0);  // Class 2
	//cout << label;

	svm->train(trainData, ROW_SAMPLE, label);
	//cout << svm->getC();

	svm->save("svm.xml");
}

double Point2PointDist(const cv::Point2f& a, const cv::Point2f& b)
{
	double res = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	return res;
}


#pragma region train

void main1()
{
	SVM_Train();
	return;
}

#pragma endregion


#pragma region test

void main()
{
	Ptr<SVM>svm = SVM::load("svm.xml");
	VideoCapture cap("../testBlue.mp4");
	//VideoCapture cap("../testRed.avi");
	Mat video1, video2;
	Mat bgrChannels[3];
	Scalar green(0, 255, 0);

	//�������svmѵ��
	//int outputImgFlag = 1;
	//int outputIndex = 1; 

	while (true)
	{
		cap >> video1;
		if (video1.empty())
			break;
		video2 = video1.clone();
		split(video1, bgrChannels);//����ͨ��
		
		//��ֵ������ɫ���� 2-0�� ��ɫ���� 0-2��Ϊ�˱�֤��ֵ��
		//��������video1
		threshold(bgrChannels[0] - bgrChannels[2], video1, 100, 255, CV_THRESH_BINARY);
		//threshold(bgrChannels[2] - bgrChannels[0], video1, 100, 255, CV_THRESH_BINARY);
		
		//��ˮ��ȥ����ͷͼ�Σ������
		//  �����ٶȱ���������̭
		//floodFill(video1, Point(0, 0), Scalar(0));
		 
		
		//ʹ��ͷ�ʹ����ں�
		//����
		Mat element = getStructuringElement(MORPH_RECT, Size(5,5));
		dilate(video1, video1, element);
		//morphologyEx(video1, video1, MORPH_CLOSE, element);

		//����
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(video1, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

		//Scalar color(255,0,0);
		//drawContours(video2, contours, 0, color, 1, 8);

		//�����С��Ӿ���
		int index = -1;
		for (auto& i : contours)
		{
			index++;
			RotatedRect rect_tmp = minAreaRect(i);
			Point2f rect_point[4];
			rect_tmp.points(rect_point);

			double width;
			double height;

			//����Ϊ�ף��̱�Ϊ��
			height = Point2PointDist(rect_point[0], rect_point[1]);
			width = Point2PointDist(rect_point[1], rect_point[2]);

			// ֻ���������������Ч,������������ (2^13)
			if (width * height > 8192)
			{
				if (width < height)
				{
					swap(width, height);
					Point2f tempP = rect_point[0];
					rect_point[0] = rect_point[1];
					rect_point[1] = rect_point[2];
					rect_point[2] = rect_point[3];
					rect_point[3] = tempP;
				}
				
				// ������ת��������͸�ӱ任������
				//Ŀ�����
				Point2f dstRect[4]{ Point2f(0,0), Point2f(0,height),Point2f(width,height), Point2f(width,0) };
				//���͸�ӱ任����
				Mat transform = getPerspectiveTransform(rect_point, dstRect);
				//��ʼ�任
				Mat testImg;
				Size2d size{width, height};
				warpPerspective(video1, testImg, transform, size);

				//imshow("test", testImg);
				
				//�������svmѵ��
				//outputImgFlag++;
				//if (outputImgFlag == 50)
				//{
				//	outputImgFlag = 1;
				//	imwrite("test" + to_string(outputIndex) + ".png", testImg);
				//	outputIndex++;
				//}

				//����С��Ԥ���õı�Ϊһ��
				resize(testImg, testImg,Size(size_X, size_Y));
				threshold(testImg, testImg,122,1, THRESH_BINARY);

				Mat testImg2;
				testImg2 = testImg.reshape(1, 1);
				testImg2.convertTo(testImg2, CV_32F);

				//float x = svm->predict(testImg2);
				////cout << x;
				//if (!x)
				//{
				//	imshow("testImg", testImg);
				//	cout << "�жϴ���2 -- ��ȷ������" << endl;
				//}
				
				// Mat res;
				//  svm->predict(testImg2, res);
				// res.at<int>(0,0) == 1
				
				if(svm->predict(testImg2))
				{
					int childIndex = hierarchy[index][2];
					if (childIndex < 0)
					{
						cout << "�жϴ���1 -- ������ȷ" << endl;
						continue;
					}
					RotatedRect targetBoard = minAreaRect(contours[childIndex]);
					Point2f rect1[4];
					targetBoard.points(rect1);
					Point centerP = targetBoard.center;

					for (int rectIndex = 0; rectIndex < 4; rectIndex++)
					{
						line(video2, rect1[rectIndex], rect1[(rectIndex + 1) % 4], Scalar(0, 255, 0), 2);
					}
					circle(video2, centerP, 1, green);
				}
			}
		}

		imshow("video1", video1);
		imshow("video2", video2);

		//�ó���ȴ�1ms ��Ȼ̫���˲���ʾ
		waitKey(1);
	}
	return;
}

#pragma endregion
