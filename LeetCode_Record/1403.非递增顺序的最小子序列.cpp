/*
 * @lc app=leetcode.cn id=1403 lang=cpp
 *
 * [1403] 非递增顺序的最小子序列
 */

// @lc code=start
// class Solution
// {
// public:
//     vector<int> minSubsequence(vector<int> &nums)
//     {
//         sort(nums.begin(), nums.end());
//         int n = nums.size();
//         int sum = accumulate(nums.begin(), nums.end(), 0)/ 2;
//         int half = 0;
//         vector<int> ans;
//         for (int i = n - 1; i >= 0; i--)
//         {
//             half += nums[i];
//             ans.push_back(nums[i]);
//             if (half > sum)
//                 return ans;
//         }
//         return ans;
//     }
// };

//优化一丢丢
class Solution
{
public:
    vector<int> minSubsequence(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0)/ 2;
        int half = nums[n-1];
        vector<int> ans {nums[n-1]};
        for (int i = n - 2; i >= 0; i--)
        {
            if (half > sum)
                return ans;
            half += nums[i];
            ans.push_back(nums[i]);
        }
        return ans;
    }
};
// @lc code=end
