#include <vector>
#include <iostream>
using namespace std;
/*
 * @lc app=leetcode.cn id=1765 lang=cpp
 *
 * [1765] 地图中的最高点
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
    {
        int i = 0, j = 0;
        for (; i < isWater.size(); i++)
        {
            bool findWater = false;
            for (j = 0; j < isWater[0].size(); j++)
            {
                if (isWater[i][j])
                {
                    findWater = true;
                    isWater[i][j] = 0;
                    continue;
                }
                if (findWater)
                {
                    isWater[i][j] = isWater[i][j - 1] + 1;
                }
                else
                {
                    isWater[i][j] = INT_MAX;
                }
                if (i > 0)
                {
                    if (isWater[i - 1][j] < isWater[i][j])
                        isWater[i][j] = isWater[i - 1][j] + 1;
                }
            }
        }
        for (i--; i >= 0; i--)
        {
            for (j = isWater[0].size() - 1; j >= 0; j--)
            {
                if (j < isWater[0].size() - 1)
                {
                    isWater[i][j] = min(isWater[i][j], isWater[i][j + 1] + 1);
                }
                if (i < isWater.size() - 1)
                {
                    isWater[i][j] = min(isWater[i][j], isWater[i + 1][j] + 1);
                }
            }
        }
        return isWater;
    }
};

// @lc code=end
