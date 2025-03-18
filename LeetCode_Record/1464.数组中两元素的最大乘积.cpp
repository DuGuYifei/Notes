#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1464 lang=cpp
 *
 * [1464] 数组中两元素的最大乘积
 */

// @lc code=start
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int max0 = 0;
        int max1 = 0;
        for (auto &i : nums)
        {
            if (i > max0)
            {
                max1 = max0;
                max0 = i;
            }
            else if (i > max1)
            {
                max1 = i;
            }
        }
        return (max0 - 1) * (max1 - 1);
    }
};
// @lc code=end
