/*
 * @lc app=leetcode.cn id=1800 lang=cpp
 *
 * [1800] 最大升序子数组和
 */

// @lc code=start
class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int ans = 0;
        int sum = 0;
        int prev = 0;
        for(auto& i : nums)
        {
            if(i > prev)
                sum += i;
            else
            {
                ans = max(ans, sum);
                sum = i;
            }
            prev = i;
        }
        ans = max(ans, sum);
        return ans;
    }
};
// @lc code=end

