/*
 * @lc app=leetcode.cn id=961 lang=cpp
 *
 * [961] 在长度 2N 的数组中找出重复 N 次的元素
 */

// n + (n-1) * 2 = 3 n - 2
// n + (n-1) = 2n - 1
// @lc code=start
class Solution
{
public:
    int repeatedNTimes(vector<int> &nums)
    {
        if (nums[1] == nums[3])
            return nums[1];
        if (nums[0] == nums[2] || nums[0] == nums[3])
            return nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == nums[i - 1])
                return nums[i];
        }
        return 0;
    }
};
// @lc code=end
