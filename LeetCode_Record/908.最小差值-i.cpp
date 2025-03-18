/*
 * @lc app=leetcode.cn id=908 lang=cpp
 *
 * [908] 最小差值 I
 */

// @lc code=start
class Solution
{
public:
    int smallestRangeI(vector<int> &nums, int k)
    {
        int maxN = 0;
        int minN = 10000;
        for (int &i : nums)
        {
            if (i > maxN)
            {
                maxN = i;
            }
            if (i < minN)
            {
                minN = i;
            }
        }
        if(minN + k >= maxN - k)
            return 0;
        return maxN - minN - 2*k;
    }
};
// @lc code=end
