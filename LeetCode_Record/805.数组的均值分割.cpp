#include <unordered_set>
#include <vector>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=805 lang=cpp
 *
 * [805] 数组的均值分割
 *
 * https://leetcode-cn.com/problems/split-array-with-same-average/description/
 *
 * algorithms
 * Hard (29.64%)
 * Likes:    117
 * Dislikes: 0
 * Total Accepted:    5.2K
 * Total Submissions: 16.3K
 * Testcase Example:  '[1,2,3,4,5,6,7,8]'
 *
 * 给定你一个整数数组 nums
 *
 * 我们要将 nums 数组中的每个元素移动到 A 数组 或者 B 数组中，使得 A 数组和 B 数组不为空，并且 average(A) ==
 * average(B) 。
 *
 * 如果可以完成则返回true ， 否则返回 false  。
 *
 * 注意：对于数组 arr ,  average(arr) 是 arr 的所有元素除以 arr 长度的和。
 *
 *
 *
 * 示例 1:
 *
 *
 * 输入: nums = [1,2,3,4,5,6,7,8]
 * 输出: true
 * 解释: 我们可以将数组分割为 [1,4,5,8] 和 [2,3,6,7], 他们的平均值都是4.5。
 *
 *
 * 示例 2:
 *
 *
 * 输入: nums = [3,1]
 * 输出: false
 *
 *
 *
 *
 * 提示:
 *
 *
 * 1 <= nums.length <= 30
 * 0 <= nums[i] <= 10^4
 *
 *
 */

// @lc code=start
class Solution
{
public:
    // dp[i + 1][nums[j] + x] = dp[i][x]
    // sum(A) = sum(nums) * k / n
    // A子集有k个数
    bool splitArraySameAverage(vector<int> &nums)
    {
        int n = nums.size(), m = n / 2;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        bool possible = false;
        for (int i = 1; i <= m; i++)
        {
            if (sum * i % n == 0) // 因为都是整数 sum * k / n 必须是整数才能使得sum(A)是整数
            {
                possible = true;
                break;
            }
        }
        if (!possible)
            return false;
        vector<unordered_set<int>> dp(m + 1);
        dp[0].insert(0);
        for (int num : nums)
            for (int i = m; i >= 1; i--) // 是自己里有几个数，从大到小是因为，dp[i]会在i-1时被插入，就改变了，其次一般平均数相同两个数组应该数量不会差太多，这样可以减少计算量
                for (int x : dp[i - 1])
                {
                    int curr = x + num; // curr 就是sum(A)
                    if (curr * n == sum * i)
                        return true;
                    dp[i].insert(curr);
                }
        return false;
    }
};
// @lc code=end
