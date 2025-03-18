#pragma once

#pragma region version 3.0

#include <vector>
#include "Params.h"
using namespace std;
#define PI 3.14159265

static const float bin_histX[Hog_bin] = { 0, Hog_angelRange, Hog_angelRange * 2,Hog_angelRange * 3 ,Hog_angelRange * 4 ,Hog_angelRange * 5 ,Hog_angelRange * 6 ,Hog_angelRange * 7,Hog_angelRange * 8 };

class Hog
{
public:
	vector<float> hogHist = vector<float>(Hog_num_features);

	friend float operator -(const Hog& a, const Hog& b)
	{
		int weight_index = -1;
		float dis = 0;
		for (int index = 0; index < Hog_num_features; index++)
		{
			dis += (a.hogHist[index] - b.hogHist[index]) * (a.hogHist[index] - b.hogHist[index]);
		}
		return dis;
	};

	Hog();
	Hog(float img[sizeX][sizeY]);
};

Hog::Hog() {};

Hog::Hog(float img[sizeX][sizeY])
{
	// calculate gradient magnitude and direction
	vector<vector<float>> magnitude(sizeX, vector<float>(sizeY));
	vector<vector<float>> direction(sizeX, vector<float>(sizeY));
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			float gx, gy;
			if (j == 0)
				gx = img[i][j + 1] - img[i][j];
			else if (j == sizeY - 1)
				gx = img[i][j] - img[i][j - 1];
			else
				gx = img[i][j + 1] - img[i][j - 1];
			
			if (i == 0)
				gy = img[i + 1][j] - img[i][j];
			else if (i == sizeX - 1)
				gy = img[i][j] - img[i - 1][j];
			else
				gy = img[i + 1][j] - img[i - 1][j];


			magnitude[i][j] = sqrt(gx * gx + gy * gy);
			direction[i][j] = atan(gy / gx) * 180 / PI;
			if (direction[i][j] < 0)
				direction[i][j] += 180;
		}
	}

	//calculate cells
	float cells[sizeX / Hog_pixelXPerCell][sizeY / Hog_pixelYPerCell][Hog_bin] = { 0 };
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			for (int k = 1; k < Hog_bin; k++)
			{
				if (direction[i][j] < bin_histX[k])
				{
					cells[i / Hog_pixelXPerCell][j / Hog_pixelYPerCell][k - 1] += (bin_histX[k] - direction[i][j]) / Hog_angelRange * magnitude[i][j];
					cells[i / Hog_pixelXPerCell][j / Hog_pixelYPerCell][k] += (direction[i][j] - bin_histX[k-1]) / Hog_angelRange * magnitude[i][j];
				}
				if (k == Hog_bin - 1 && direction[i][j] >= bin_histX[k])
				{
					cells[i / Hog_pixelXPerCell][j / Hog_pixelYPerCell][k] += (180 - direction[i][j]) / Hog_angelRange * magnitude[i][j];
					cells[i / Hog_pixelXPerCell][j / Hog_pixelYPerCell][0] += (direction[i][j] - bin_histX[k]) / Hog_angelRange * magnitude[i][j];
				}
			}
		}
	}

	//calculate blocks
	int index_hogHist = 0;
	for (int i = 0; i < Hog_numX_block; i++)
	{
		for (int j = 0; j < Hog_numY_block; j++)
		{
			vector<float> block(Hog_cellXPerBlock * Hog_cellYPerBlock * Hog_bin);
			for (int k = 0; k < Hog_cellXPerBlock;k ++)
			{
				for (int m = 0; m < Hog_cellYPerBlock; m++)
				{
					for (int l = 0; l < Hog_bin; l++)
					{
						block[(k * Hog_cellYPerBlock + m) * Hog_bin + l] = cells[i + k][j + m][l];
					}
				}
			}
			float base = 0;
			for (auto& col : block)
			{
				base += col * col;
			}
			base = sqrt(base);
			for (auto& col : block)
			{
				col /= base;
				hogHist[index_hogHist] = col;
				index_hogHist++;
			}
		}
	}
}

#pragma endregion



#pragma region version 2.0

//#include <vector>
//using namespace std;
//
//const int Bins = 9;
//const int num_hog = Bins * SideRange * SideRange;
//static const int SideRange = 6;
//static const float HOG_weight_face[SideRange * SideRange] = 
//{
//	4,	4,	3,	3,	4,	4,
//	4,	4,	4,	4,	4,	4,
//	1,	1,	1.5,1.5,1,	1,
//	1,	1.5,1.5,1.5,1.5,1,
//	1,	1.5,2,	2,	1.5,1,
//	1,	2,	3,	3,	2,	1
//};
//
//
//class Hog
//{
//public:
//	// int or float is depend on your output in pythonS
//	vector<float> hogHist = vector<float>(num_hog);
//	friend float operator -(const Hog& a, const Hog& b)
//	{
//		int weight_index = -1;
//		float dis = 0;
//		for (int index = 0; index < num_hog; index++)
//		{
//			dis += HOG_weight_face[index] * (a.hogHist[index] - b.hogHist[index]) * (a.hogHist[index] - b.hogHist[index]) / (a.hogHist[index] + b.hogHist[index]);
//			//dis += (a.ULBPH[index] - b.ULBPH[index]) * (a.ULBPH[index] - b.ULBPH[index]);
//		}
//		return dis;
//	};
//
//	//------------------------
//	//default must be here, it is the problem of c++
//	Hog();
//	//------------------------
//
//	//------------------------
//	//Hog(float img[24][24]); 
//	//------------------------
//
//	//---------------------------------------------
//	//Here you can read the hig histograms of one image from a vector which will be read from text
//	//You don't need output the attribute into your text, because we will read it for both Hog and LBPH.
//	/*
//	* The sequence of your output in python should be like this:
//	int num = 0; // 0,1,2,3 is train, 4 is test
//	for (int i = 0; i < 3; i++)
//	{
//		Open 3 files one by one
//		for (int j = 0; j < RowsInText; j++)
//		{
//			if (num < 4)
//			{
//				//out put to train
//				num++;
//			}
//			if (num == 4)
//			{
//				//out put to test
//				num = 0;
//			}
//		}
//	}
//	*/
//	//Hog(vector<float> nums);
//	//-----------------------------------
//
//};
//
//Hog::Hog() {};
//
////Hog::Hog(vector<float> nums)
////{
////	hogHist = nums;
////}

#pragma endregion


#pragma region version 1.0

//#include <iostream>
//#include <fstream>
//#include <cmath>
//#include <vector>
//#define CELL_SIZE_X 4
//#define NUM_BINS 4
//
//float** Gy(float** img, int img_size)
//{
//    float** Gy = new float* [img_size];
//    for (int i = 0; i < img_size; i++)
//    {
//        Gy[i] = new float[img_size];
//    }
//    for (int i = 0; i < img_size; i++)
//    {
//        for (int j = 0; j < img_size; j++)
//        {
//            if (i >= (img_size - 1))
//            {
//                Gy[i][j] = img[i][j] - img[i - 1][j];
//            }
//            else if (i < 1)
//            {
//                Gy[i][j] = img[i + 1][j] - img[i][j];
//            }
//            else
//            {
//                Gy[i][j] = img[i + 1][j] - img[i - 1][j];
//            }
//        }
//    }
//    return Gy;
//}
//
//float** Gx(float** img, int img_size)
//{
//    float** Gx = new float* [img_size];
//    for (int i = 0; i < img_size; i++)
//    {
//        Gx[i] = new float[img_size];
//    }
//    for (int i = 0; i < img_size; i++)
//    {
//        for (int j = 0; j < img_size; j++)
//        {
//            if (j >= (img_size - 1))
//            {
//                Gx[i][j] = img[i][j] - img[i][j - 1];
//            }
//            else if (j < 1)
//            {
//                Gx[i][j] = img[i][j + 1] - img[i][j];
//            }
//            else
//            {
//                Gx[i][j] = img[i][j + 1] - img[i][j - 1];
//            }
//        }
//    }
//    return Gx;
//}
//
//
//
//float*** Gmatrices(float** img, int img_size)
//{
//    float*** Gmatrices = new float** [2];
//    Gmatrices[0] = new float* [img_size];
//    Gmatrices[1] = new float* [img_size];
//    for (int i = 0; i < img_size; i++)
//    {
//        Gmatrices[0][i] = new float[img_size];
//        Gmatrices[1][i] = new float[img_size];
//    }
//    float** matrixX = Gx(img, img_size);
//    float** matrixY = Gy(img, img_size);
//    for (int i = 0; i < img_size; i++)
//    {
//        for (int j = 0; j < img_size; j++)
//        {
//            Gmatrices[0][i][j] = std::sqrt((matrixX[i][j] * matrixX[i][j]) + (matrixY[i][j] * matrixY[i][j]));
//            if (matrixX[i][j] == 0)
//            {
//                Gmatrices[1][i][j] = std::atan(1) * 2;
//            }
//            else Gmatrices[1][i][j] = std::atan((matrixY[i][j]) / matrixX[i][j]);
//        }
//    }
//    return Gmatrices;
//}
//
//float* split_cells(float** mag, float** dir, int img_size)
//{
//    int num_cells = (img_size) / CELL_SIZE_X;
//    int* cell_begin = new int[num_cells];
//    std::vector<float*> histograms;
//    for (int i = 0; i < num_cells; i++)
//    {
//        cell_begin[i] = i * CELL_SIZE_X;
//    }
//    float theta = std::atan(1) * 4 / NUM_BINS;
//    for (int h = 0; h < num_cells; h++)
//    {
//        float* hist = new float[NUM_BINS];
//        for (int i = 0; i < NUM_BINS; i++)
//        {
//            hist[i] = 0;
//        }
//        for (int i = cell_begin[h]; i < (cell_begin[h] + CELL_SIZE_X); i++)
//        {
//            for (int j = cell_begin[h]; j < (cell_begin[h] + CELL_SIZE_X); j++)
//            {
//                float val = (dir[i][j] / theta);
//                int n = int(std::floor(val));
//                hist[n] = hist[n] + mag[i][j] * (1 - (val - n));
//                hist[(n + 1) % NUM_BINS] = hist[(n + 1) % NUM_BINS] + mag[i][j] * (val - n);
//
//            }
//        }
//        histograms.push_back(hist);
//
//    }
//    int num_hist = histograms.size();
//    float* reshape_histogram = new float[NUM_BINS * num_hist + 1];
//    for (int i = 0; i < num_hist; i++)
//    {
//        float* hist = histograms[i];
//        for (int j = 0; j < NUM_BINS; j++)
//        {
//            reshape_histogram[j + i * NUM_BINS + 1] = hist[j];
//        }
//    }
//    reshape_histogram[0] = num_hist * NUM_BINS;
//    return reshape_histogram;
//}
//
//int main()
//{
//    std::fstream myfile, train_write, test_write;
//    myfile.open("x24x24.txt");
//    train_write.open("train.txt");
//    test_write.open("test.txt");
//    int num_I;
//    //int attr[8] = { 0 };
//
//    myfile >> num_I >> num_I;
//    int img_size = std::sqrt(num_I);
//    std::vector<float**> images;
//    std::vector<int*> attrs;
//    int it = 0;
//    while (!myfile.eof())
//    {
//        //std::cout << "popyn";
//        if (myfile.eof())
//        {
//            break;
//        }
//        int* attr = new int[8];
//        float** img = new float* [img_size];
//        for (int i = 0; i < img_size; i++)
//        {
//            img[i] = new float[img_size];
//        }
//        //std::vector<do>
//        for (int i = 0; i < img_size; i++)
//        {
//            for (int j = 0; j < img_size; j++)
//            {
//                myfile >> img[i][j];
//            }
//        }
//        for (int i = 0; i < 8; i++)
//        {
//            myfile >> attr[i];
//        }
//        images.push_back(img);
//        attrs.push_back(attr);
//        float*** data;
//        float* hist;
//        if (it % 5 == 0)
//        {
//            data = Gmatrices(img, img_size);
//            hist = split_cells(data[0], data[1], img_size);
//            it = it + 1;
//            int num_items = hist[0];
//            test_write << attr[1] << " ";
//            for (int i = 1; i <= num_items; i++)
//            {
//                test_write << hist[i] << " ";
//            }
//            test_write << std::endl;
//        }
//        else
//        {
//            data = Gmatrices(img, img_size);
//            hist = split_cells(data[0], data[1], img_size);
//            it = it + 1;
//            int num_items = hist[0];
//            train_write << attr[1] << " ";
//            for (int i = 1; i <= num_items; i++)
//            {
//                train_write << hist[i] << " ";
//            }
//            train_write << std::endl;
//        }
//    }
//
//    train_write.close();
//    test_write.close();
//    myfile.close();
//
//
//    std::cout << num_I;
//}

#pragma endregion