#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=813 lang=cpp
 *
 * [813] 最大平均值和的分组
 *
 * https://leetcode-cn.com/problems/largest-sum-of-averages/description/
 *
 * algorithms
 * Medium (55.88%)
 * Likes:    248
 * Dislikes: 0
 * Total Accepted:    11.6K
 * Total Submissions: 20.3K
 * Testcase Example:  '[9,1,2,3,9]\n3'
 *
 * 给定数组 nums 和一个整数 k 。我们将给定的数组 nums 分成 最多 k 个相邻的非空子数组 。 分数 由每个子数组内的平均值的总和构成。
 * 
 * 注意我们必须使用 nums 数组中的每一个数进行分组，并且分数不一定需要是整数。
 * 
 * 返回我们所能得到的最大 分数 是多少。答案误差在 10^-6 内被视为是正确的。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: nums = [9,1,2,3,9], k = 3
 * 输出: 20.00000
 * 解释: 
 * nums 的最优分组是[9], [1, 2, 3], [9]. 得到的分数是 9 + (1 + 2 + 3) / 3 + 9 = 20. 
 * 我们也可以把 nums 分成[9, 1], [2], [3, 9]. 
 * 这样的分组得到的分数为 5 + 2 + 6 = 13, 但不是最大值.
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: nums = [1,2,3,4,5,6,7], k = 4
 * 输出: 20.50000
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 <= nums.length <= 100
 * 1 <= nums[i] <= 10^4
 * 1 <= k <= nums.length
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<double> prefix(n+1);
        // prefix[i] 是前i项和
        for(int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];
        
        // vector<vector<double>> dp(n + 1, vector<double>(k + 1));
        
        // // 初始化只分一组的值
        // for(int i = 1; i <= n; i++)
        //     dp[i][1] = prefix[i]/i;
        
        // // 对于分多少组一个个过
        // for(int i = 2; i <= k; i++)
        //     // 对于前多少项分组一个个来，多少项至少得比分多少组大
        //     for(int j = i; j <= n; j++)
        //         // 根据转移方程中所说需要遍历出最大值作为dp值，起始于少一组，终结于有多少项
        //         for(int x = i - 1; x < j; x++)
        //             dp[j][i] = max(dp[j][i], dp[x][i-1] + (prefix[j] - prefix[x])/(j-x));
        
        // return dp[n][k];

        // 算法上没有任何变化，只是将空间重复利用，少个一维
        vector<double>dp(n+1);
        for(int i = 1; i <= n; i++)
            dp[i] = prefix[i]/i;
        for(int i = 2; i <= k; i++)
            for(int j = n; j >= i; j--)
                for(int x = i - 1; x < j; x++)
                    dp[j] = max(dp[j], dp[x] + (prefix[j] - prefix[x])/(j-x));
        return dp[n];
    }
};
// @lc code=end

