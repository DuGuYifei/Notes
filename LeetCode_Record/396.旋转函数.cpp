#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=396 lang=cpp
 *
 * [396] 旋转函数
 */

// @lc code=start
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        int fn = 0;
        int sum = 0;
        for(int i = 0; i < n;i++)
        {
            sum += nums[i];
            fn += i * nums[i];
        }
        int ans = fn;
        for(int i = 1; i < n ; i ++)
        {
            fn += sum - n * nums[n - i];
            ans = max(ans, fn);    
        }
        return ans;
    }
};
// @lc code=end

