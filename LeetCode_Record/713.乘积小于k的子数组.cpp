#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=713 lang=cpp
 *
 * [713] 乘积小于K的子数组
 */

// @lc code=start
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        // for(int i = 0;i<n;i++)
        // {
        //     int mul = 1;
        //     for(int j = i;j<n;j++)
        //     {
        //         mul *= nums[j];
        //         if(mul<k)
        //         {
        //             ans++;
        //         }
        //         else
        //         {
        //             break;
        //         }
        //     }
        // }
        // return ans;
        // int mul = 1;
        // int i = 0;
        // for(int j = 0;j < n;j++)
        // {
        //     mul *= nums[j];
        //     while(mul >= k && i <= j)
        //     {
        //         mul/=nums[i++];
        //     }
        //     ans += j-i+1;
        // }
        vector<double> logs(n + 1);
        for(int i = 0;i <n ;i++)
        {
            logs[i+1] = log(nums[i]) + logs[i];
        }
        double logk = log(k);
        for(int i = 0;i < n ;i ++)
        {
            // logs[i+1]-logs[l] + 1e-10 < logk
            // logs[l] > logs[i+1] - logk + 1e-10
            int l = upper_bound(logs.begin(), logs.begin()+i+1,logs[i+1]-logk + 1e-10) - logs.begin();
            ans += i - l + 1;
        }
        return ans;
    }
};
// @lc code=end

