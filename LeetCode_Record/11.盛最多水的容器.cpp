#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        // int maxw = 0;
        // int maxl = height[0];
        // for (int i = 0; i < height.size() - 1; i++)
        // {
        //     if (i > 0 && maxl >= height[i])
        //     {
        //         continue;
        //     }

        //     for (int j = i + 1; j < height.size(); j++)
        //     {
        //         int water = (j - i) * min(height[i], height[j]);
        //         maxw = max(water, maxw);
        //     }
        // }
        // return maxw;

        int left = 0, right = height.size() - 1, maxw = 0;

        while (left < right)
        {
            int area = (right - left) * min(height[left], height[right]);
            maxw = max(maxw, area);
            if (height[left] <= height[right])
            {
                left++;
            }
            else
                right--;
        }

        return maxw;
    }
};
// @lc code=end
