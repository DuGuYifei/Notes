#pragma once
#include <vector>
#include "Params.h"
using namespace std;

static const int ULBP_table[256] = { 1,2,3,4,5,0,6,7,8,0,0,0,9,0,10,11,12,0,0,0,0,0,0,0,13,0,0,0,14,0,15,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,0,0,0,0,0,0,0,19,0,0,0,20,0,21,22,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,25,0,0,0,0,0,0,0,26,0,0,0,27,0,28,29,30,31,0,32,0,0,0,33,0,0,0,0,0,0,0,34,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,36,37,38,0,39,0,0,0,40,0,0,0,0,0,0,0,41,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,42,43,44,0,45,0,0,0,46,0,0,0,0,0,0,0,47,48,49,0,50,0,0,0,51,52,53,0,54,55,56,57,58 };


static const float weight_face[LBPH_blockX * LBPH_blockY] =
//{ 4,3,3,4,2,1.5,1.5,2,1,2,2,1,1,3,3,1 }; //4*4
//{ 3,2,3,1,2,1,1.5,3,1.5 };
//{ 1,1,1,1,1,1,1,1,1 };
//{4,4,4,4,3,2,2,3,1,3,3,1,1.5,3,3,1.5};
{
	2,	1.5,	1.5,	1,		1,		1.5,	1.5,	2,
	4,	4,		4,		1,		1,		4,		4,		4,
	2,	2,		2,		1.5,	1.5,	2,		2,		2,
	1,	1,		1,		1.5,	1.5,	1,		1,		1,
	1,	1,		1.5,	2,		2,		1.5,	1,		1,
	1,	1,		1.5,	2,		2,		1.5,	1,		1,
	1,	1,		2,		3,		3,		2,		1,		1,
	1,	1,		2,		3,		3,		2,		1,		1
};

class LBPH
{
public:
	vector<int> ULBPH = vector<int>(LBPH_blockXY59, 0);

	// chi-square distance
	friend float operator -(const LBPH& a, const LBPH& b)
	{
		int weight_index = -1;
		float dis = 0;
		for (int i = 0; i < LBPH_blockX; i++)
		{
			for (int j = 0; j < LBPH_blockY; j++)
			{
				weight_index++;
				for (int k = 0; k < 59; k++)
				{
					int index = (i * LBPH_blockX + j) * 59 + k;
					if (a.ULBPH[index] + b.ULBPH[index] == 0)
					{
						continue;
					}
					dis += weight_face[weight_index] * (a.ULBPH[index] - b.ULBPH[index]) * (a.ULBPH[index] - b.ULBPH[index]) / (a.ULBPH[index] + b.ULBPH[index]);
					//dis += (a.ULBPH[index] - b.ULBPH[index]) * (a.ULBPH[index] - b.ULBPH[index]);
				}
			}
		}
		return dis;
	};

	LBPH();
	LBPH(float image[sizeX][sizeY]);
	//LBPH(vector<int> ulpbh);
};

LBPH::LBPH() {};
LBPH::LBPH(float image[sizeX][sizeY])
{
	int ULBP_img[sizeX][sizeY];
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			// if 60 then it is outline
			ULBP_img[i][j] = 60;
			if (i == 0 || i == 23 || j == 0 || j == 23)
				continue;

			//calculate ulbp
			int ulbp;
			//if (i == 0 || j == 0)
			//{
			//	ulbp = 1;
			//}
			//else
				image[i - 1][j - 1]	< image[i][j] ? ulbp = 0 : ulbp = 1;
			ulbp <<= 1;
			//if (i == 0)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i - 1][j]		< image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (i == 0 || j == 23)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i - 1][j + 1] < image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (j == 23)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i][j + 1]		< image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (i == 23 || j == 23)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i + 1][j + 1] < image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (i == 23)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i + 1][j]		< image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (i == 23 || j == 0)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i + 1][j - 1] < image[i][j] ? ulbp += 0 : ulbp += 1;
			ulbp <<= 1;
			//if (j == 0)
			//{
			//	ulbp += 1;
			//}
			//else
				image[i][j - 1]		< image[i][j] ? ulbp += 0 : ulbp += 1;

			ULBP_img[i][j] = ULBP_table[ulbp];
		}
	}

	// divide into n*n blocks
	for (int i = 0; i < LBPH_blockX; i++)
	{
		for (int j = 0; j < LBPH_blockY; j++)
		{
			for (int x = i * LBPH_cellPerBlockX; x < (i + 1) * LBPH_cellPerBlockX; x++)
			{
				for (int y = j * LBPH_cellPerBlockY; y < (j + 1) * LBPH_cellPerBlockY; y++)
				{
					if (ULBP_img[x][y] != 60)
						ULBPH[(i * LBPH_blockY + j) * 59 + ULBP_img[x][y]]++;
				}
			}
		}
	}
}

//LBPH::LBPH(vector<int> ulpbh)
//{
//	ULBPH = ulpbh;
//}


// get the table of all binary number of ULBP
//int getHopCount(int i)
//{
//    int a[8] = { 0 };
//    int k = 7;
//    int cnt = 0;
//    while (i)
//    {
//        a[k] = i & 1;
//        i >>= 1;
//        --k;
//    }
//    for (int k = 0; k < 8; ++k)
//    {
//        if (a[k] != a[k + 1 == 8 ? 0 : k + 1])
//        {
//            ++cnt;
//        }
//    }
//    return cnt;
//}
//
//void lbp59table(int table[256])
//{
//    int temp = 1;
//    for (int i = 0; i < 256; ++i)
//    {
//        if (getHopCount(i) <= 2)
//        {
//            table[i] = temp;
//            temp++;
//        }
//        // printf("%d\n",table[i]);  
//    }
//}