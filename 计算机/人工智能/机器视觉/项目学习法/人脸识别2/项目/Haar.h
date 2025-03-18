#pragma once
#include "Params.h"
class Haar
{
public:
	vector<float> haarVector = vector<float>(Haar_num_features);

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


	float HaarEdgeMap[sizeX][sizeY] = { 0 };
	float HaarLineMap[sizeX][sizeY] = { 0 };
	float HaarFourMap[sizeX][sizeY] = { 0 };
	float EdgeVal = 0, LineVal = 0, FourVal = 0;
	for (int i = 0; i < sizeX; i++)
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

				for (int ii = i; ii < (i + Haar_pixelXPerCell); ii++)
				{
					for (int jj = j; jj < (j + Haar_pixelYPerCell); jj++)
					{
						HaarEdgeMap[ii][jj] = EdgeVal;
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
				for (int ii = i; ii < (i + Haar_pixelXPerCell); ii++)
				{
					for (int jj = j; jj < (j + Haar_pixelYPerCell); jj++)
					{
						HaarLineMap[ii][jj] = LineVal;
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
				for (int ii = i; ii < (i + Haar_FourRectSize); ii++)
				{
					for (int jj = j; jj < (j + Haar_FourRectSize); jj++)
					{
						HaarFourMap[ii][jj] = FourVal;
					}
				}
			}

		}
	}
	//std::vector<float> toBeHaar = std::vector<float>(Haar_num_features);
	int index = 0;
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			haarVector[index++] = HaarEdgeMap[i][j];
			haarVector[index++] = HaarLineMap[i][j];
			haarVector[index++] = HaarFourMap[i][j];
		}
	}

	//haarVector = toBeHaar;
}
