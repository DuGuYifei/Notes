#pragma once
#pragma once
#include "Params.h"
#include <vector>

class Haar
{
public:
	std::vector<float> haarVector = std::vector<float>(Haar_num_features);

	friend float operator -(const Haar& a, const Haar& b)
	{
		int weight_index = -1;
		float dis = 0;
		for (int index = 0; index < Haar_num_features; index++)
		{
			dis += (a.haarVector[index] - b.haarVector[index]) * (a.haarVector[index] - b.haarVector[index]);
		}
		return dis;
	};
	Haar();
	Haar(float img[sizeX][sizeY]);
};

Haar::Haar() {};
Haar::Haar(float img[sizeX][sizeY])
{	
	float I = 0;
	//compute integral image
	float sum[sizeX][sizeY] = { 0 };
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{

			I = img[i][j];
			if (j > 0)
				I += sum[i][j - 1];
			if (i > 0)
				I += sum[i - 1][j];
			if (i > 0 && j > 0)
				I -= sum[i - 1][j - 1];
			sum[i][j] = I;
			}
		}
	
	
	bool HaarEdgeMap[sizeX][sizeY] = { 0 };
	bool HaarLineMap[sizeX][sizeY] = { 0 };
	bool HaarFourMap[sizeX][sizeY] = { 0 };
	float EdgeVal = 0, LineVal = 0, FourVal = 0;
	for(int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			if (((i + Haar_pixelXPerCell) < sizeX) && ((j + Haar_pixelYPerCell) < sizeY))
			{
				EdgeVal = sum[i + Haar_pixelXPerCell][j + Haar_pixelYPerCell]
					- 2 * (sum[i + Haar_pixelXPerCell][j + (Haar_pixelYPerCell / 2)])
					+ sum[i + Haar_pixelXPerCell][j]
					- sum[i][j + Haar_pixelYPerCell]
					+ 2 * (sum[i][j + (Haar_pixelYPerCell / 2)])
					- sum[i][j];

				if (EdgeVal > HaarEdgeThreshold)
				{
					for (int ii = i; ii < (i + Haar_pixelXPerCell); ii++)
					{
						for (int jj = j; jj < (j + Haar_pixelYPerCell); jj++)
						{
							HaarEdgeMap[ii][jj] = true;
						}
					}
				}
				LineVal = sum[i + Haar_pixelXPerCell][j + Haar_pixelYPerCell]
					- sum[i + Haar_pixelXPerCell][j]
					- 2 * (sum[i + (2 * Haar_pixelXPerCell / 3)][j + Haar_pixelYPerCell])
					+ 2 * (sum[i + (2 * Haar_pixelXPerCell / 3)][j])
					+ 2 * (sum[i + (Haar_pixelXPerCell / 3)][j + Haar_pixelYPerCell])
					- 2 * (sum[i + (Haar_pixelXPerCell / 3)][j])
					- sum[i][j + Haar_pixelYPerCell]
					+ sum[i][j];
				if (LineVal > HaarLineThreshold)
				{
					for (int ii = i; ii < (i + Haar_pixelXPerCell); ii++)
					{
						for (int jj = j; jj < (j + Haar_pixelYPerCell); jj++)
						{
							HaarLineMap[ii][jj] = true;
						}
					}
				}
			}
			if (((i + Haar_FourRectSize) < sizeX) && ((j + Haar_FourRectSize) < sizeY))
			{
				FourVal = sum[i + Haar_FourRectSize][j + Haar_FourRectSize]
					- 2 * (sum[i + Haar_FourRectSize][j + (Haar_FourRectSize / 2)])
					+ sum[i + Haar_FourRectSize][j]
					- 2 * (sum[i + (Haar_FourRectSize / 2)][j + Haar_FourRectSize])
					+ 4 * (sum[i + (Haar_FourRectSize / 2)][j + (Haar_FourRectSize / 2)])
					- 2 * (sum[i + (Haar_FourRectSize / 2)][j])
					+ sum[i][j + Haar_FourRectSize]
					- 2 * (sum[i][j + (Haar_FourRectSize / 2)])
					+ sum[i][j];
				if (FourVal > HaarFourRectangleThreshold)
				{
					for (int ii = i; ii < (i + Haar_FourRectSize); ii++)
					{
						for (int jj = j; jj < (j + Haar_FourRectSize); jj++)
						{
							HaarFourMap[ii][jj] = true;
						}
					}
				}
			}
			
		}
	}
	std::vector<float> toBeHaar = std::vector<float>(Haar_num_features);
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			toBeHaar.push_back(HaarEdgeMap[i][j]);
			printf("%d %d %d \n", HaarEdgeMap[i][j], HaarLineMap[i][j], HaarFourMap[i][j]);
			toBeHaar.push_back(HaarLineMap[i][j]);
			toBeHaar.push_back(HaarFourMap[i][j]);
		}
	}
	
	haarVector = toBeHaar;
}

