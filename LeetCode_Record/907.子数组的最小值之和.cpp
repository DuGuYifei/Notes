#include <vector>
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=907 lang=cpp
 *
 * [907] 子数组的最小值之和
 *
 * https://leetcode-cn.com/problems/sum-of-subarray-minimums/description/
 *
 * algorithms
 * Medium (32.89%)
 * Likes:    445
 * Dislikes: 0
 * Total Accepted:    23.7K
 * Total Submissions: 66.1K
 * Testcase Example:  '[3,1,2,4]'
 *
 * 给定一个整数数组 arr，找到 min(b) 的总和，其中 b 的范围为 arr 的每个（连续）子数组。
 * 
 * 由于答案可能很大，因此 返回答案模 10^9 + 7 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：arr = [3,1,2,4]
 * 输出：17
 * 解释：
 * 子数组为 [3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。 
 * 最小值为 3，1，2，4，1，1，2，1，1，1，和为 17。
 * 
 * 示例 2：
 * 
 * 
 * 输入：arr = [11,81,94,43,3]
 * 输出：444
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> right(n), left(n);
        stack<int> mono;
        for(int i = n - 1; i >= 0; i--)
        {
            while(!mono.empty() && arr[mono.top()] >= arr[i])
                mono.pop();
            right[i] = mono.empty()? n : mono.top();
            mono.push(i);
        }
        mono = stack<int> ();
        for(int i = 0; i < n; i++)
        {
            while(!mono.empty() && arr[i] < arr[mono.top()])
                mono.pop();
            left[i] = mono.empty()? -1 : mono.top();
            mono.push(i);
        }
        long long ans = 0;
        long long mod = 1e9+7;
        for(int i = 0; i < n; i++)
        {
            ans = (ans + (long long)(i - left[i]) * (right[i] - i) * arr[i]) % mod;
        }
        return ans;
    }
};
// @lc code=end

