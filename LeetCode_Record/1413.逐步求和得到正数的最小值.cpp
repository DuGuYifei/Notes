#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1413 lang=cpp
 *
 * [1413] 逐步求和得到正数的最小值
 */

// @lc code=start
class Solution
{
public:
    int minStartValue(vector<int> &nums)
    {
        int ans = 1;
        int sum = 1;
        for (auto &i : nums)
        {
            sum += i;
            if (sum < 1)
            {
                ans += 1 - sum;
                sum = 1;
            }
        }
        return ans;
    }
};
// @lc code=end
