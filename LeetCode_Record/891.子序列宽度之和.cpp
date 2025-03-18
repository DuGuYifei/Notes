#include <algorithm>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=891 lang=cpp
 *
 * [891] 子序列宽度之和
 *
 * https://leetcode-cn.com/problems/sum-of-subsequence-widths/description/
 *
 * algorithms
 * Hard (33.75%)
 * Likes:    76
 * Dislikes: 0
 * Total Accepted:    4.5K
 * Total Submissions: 12K
 * Testcase Example:  '[2,1,3]'
 *
 * 一个序列的 宽度 定义为该序列中最大元素和最小元素的差值。
 * 
 * 给你一个整数数组 nums ，返回 nums 的所有非空 子序列 的 宽度之和 。由于答案可能非常大，请返回对 10^9 + 7 取余 后的结果。
 * 
 * 子序列 定义为从一个数组里删除一些（或者不删除）元素，但不改变剩下元素的顺序得到的数组。例如，[3,6,2,7] 就是数组
 * [0,3,1,6,2,2,7] 的一个子序列。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [2,1,3]
 * 输出：6
 * 解释：子序列为 [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3] 。
 * 相应的宽度是 0, 0, 0, 1, 1, 2, 2 。
 * 宽度之和是 6 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [2]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^5
 * 
 * 
 */

// @lc code=start
// class Solution {
// public:
//     const int mod  = 1e9 + 7;
//     int sumSubseqWidths(vector<int>& nums) {
//         int n = nums.size();
//         if(n == 1) return 0;
//         sort(nums.begin(), nums.end());
//         int ans = 0;
//         vector<int> power(n, 0);
//         power[1] = 1;
//         for(int i = 0; i < n; i++)
//             for(int j = i + 1; j < n; j++)
//             {
//                 if(!power[j - i])
//                     power[j - i] = power[j-i-1] * 2 % mod;
//                 ans = (ans + (long long)(nums[j] - nums[i]) * power[j - i] % mod) % mod;
//             }
//         return ans;
//     }
// };
// 将上面 nums[j] - nums[i] 分配律在重新结合率计算
class Solution {
public:
    const int mod  = 1e9 + 7;
    int sumSubseqWidths(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        long long power = 2;
        for(int i = n - 2; i >= 0; i--)
        {
            ans = (ans + (nums[n - i - 1]- nums[i]) * (power - 1)) % mod;
            power = power * 2 % mod;
        }
        return ans;
    }
};
// @lc code=end

