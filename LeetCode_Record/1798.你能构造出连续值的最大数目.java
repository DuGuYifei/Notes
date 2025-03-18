import java.util.Arrays;

/*
 * @lc app=leetcode.cn id=1798 lang=java
 *
 * [1798] 你能构造出连续值的最大数目
 *
 * https://leetcode-cn.com/problems/maximum-number-of-consecutive-values-you-can-make/description/
 *
 * algorithms
 * Medium (53.57%)
 * Likes:    189
 * Dislikes: 0
 * Total Accepted:    19.2K
 * Total Submissions: 27.3K
 * Testcase Example:  '[1,3]'
 *
 * 给你一个长度为 n 的整数数组 coins ，它代表你拥有的 n 个硬币。第 i 个硬币的值为 coins[i]
 * 。如果你从这些硬币中选出一部分硬币，它们的和为 x ，那么称，你可以 构造 出 x 。
 * 
 * 请返回从 0 开始（包括 0 ），你最多能 构造 出多少个连续整数。
 * 
 * 你可能有多个相同值的硬币。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：coins = [1,3]
 * 输出：2
 * 解释：你可以得到以下这些值：
 * - 0：什么都不取 []
 * - 1：取 [1]
 * 从 0 开始，你可以构造出 2 个连续整数。
 * 
 * 示例 2：
 * 
 * 
 * 输入：coins = [1,1,1,4]
 * 输出：8
 * 解释：你可以得到以下这些值：
 * - 0：什么都不取 []
 * - 1：取 [1]
 * - 2：取 [1,1]
 * - 3：取 [1,1,1]
 * - 4：取 [4]
 * - 5：取 [4,1]
 * - 6：取 [4,1,1]
 * - 7：取 [4,1,1,1]
 * 从 0 开始，你可以构造出 8 个连续整数。
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [1,4,10,3,1]
 * 输出：20
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * coins.length == n
 * 1 
 * 1 
 * 
 * 
 */

// @lc code=start
class Solution {
    public int getMaximumConsecutive(int[] coins) {
        int res = 1;
        Arrays.sort(coins);
        for(int i : coins){
            if(i > res)
                break;
            res += i;
        }
        return res;
    }
}
// @lc code=end

