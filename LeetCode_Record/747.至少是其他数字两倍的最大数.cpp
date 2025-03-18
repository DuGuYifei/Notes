#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=747 lang=cpp
 *
 * [747] 至少是其他数字两倍的最大数
 */

// @lc code=start
class Solution
{
public:
    int dominantIndex(vector<int> &nums)
    {
        int first = -1, second = -1, index = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > first)
            {
                second = first;
                first = nums[i];
                index = i;
            }
            else if (nums[i] > second)
            {
                second = nums[i];
            }
        }
        if (first >=second * 2)
            return index;
        return -1;
    }
};
// @lc code=end
