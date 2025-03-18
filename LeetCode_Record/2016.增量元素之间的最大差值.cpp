#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2016 lang=cpp
 *
 * [2016] 增量元素之间的最大差值
 */

// @lc code=start
class Solution
{
public:
    int maximumDifference(vector<int> &nums)
    {
        int maxD = -1, minN = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] < minN)
                minN = nums[i];
            if (nums[i] > minN)
                maxD = max(nums[i]-minN,maxD);
        }
        return maxD;
    }
};
// @lc code=end
