#include <vector>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=1799 lang=cpp
 *
 * [1799] N 次操作后的最大分数和
 *
 * https://leetcode-cn.com/problems/maximize-score-after-n-operations/description/
 *
 * algorithms
 * Hard (52.54%)
 * Likes:    84
 * Dislikes: 0
 * Total Accepted:    11.3K
 * Total Submissions: 17.4K
 * Testcase Example:  '[1,2]'
 *
 * 给你 nums ，它是一个大小为 2 * n 的正整数数组。你必须对这个数组执行 n 次操作。
 * 
 * 在第 i 次操作时（操作编号从 1 开始），你需要：
 * 
 * 
 * 选择两个元素 x 和 y 。
 * 获得分数 i * gcd(x, y) 。
 * 将 x 和 y 从 nums 中删除。
 * 
 * 
 * 请你返回 n 次操作后你能获得的分数和最大为多少。
 * 
 * 函数 gcd(x, y) 是 x 和 y 的最大公约数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums = [1,2]
 * 输出：1
 * 解释：最优操作是：
 * (1 * gcd(1, 2)) = 1
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums = [3,4,6,8]
 * 输出：11
 * 解释：最优操作是：
 * (1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
 * 
 * 
 * 示例 3：
 * 
 * 输入：nums = [1,2,3,4,5,6]
 * 输出：14
 * 解释：最优操作是：
 * (1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 7
 * nums.length == 2 * n
 * 1 <= nums[i] <= 10^6
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> gcds(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                gcds[i][j] = gcd(nums[i], nums[j]);
            }
        }
        int m = 1 << n;
        vector<int>dp(m); // 为1未被删除
        for(int i = 0; i < m; i++){
            int cnt = __builtin_popcount(i);
            if(cnt % 2 == 0)
                for(int j = 0; j < n; j++)
                    if(i >> j & 1)
                        for(int k = j+1; k < n; k++)
                            if(i >> k & 1)
                                dp[i] = max(dp[i], dp[i ^ (1 << j) ^ (1 << k)] + cnt/2 * gcds[j][k]);
                
        }
        return dp[m-1];
    }
};
// @lc code=end

