/*
 * @lc app=leetcode.cn id=1250 lang=java
 *
 * [1250] 检查「好数组」
 *
 * https://leetcode-cn.com/problems/check-if-it-is-a-good-array/description/
 *
 * algorithms
 * Hard (57.59%)
 * Likes:    89
 * Dislikes: 0
 * Total Accepted:    14.2K
 * Total Submissions: 20.4K
 * Testcase Example:  '[12,5,7,23]'
 *
 * 给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。
 * 
 * 假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums = [12,5,7,23]
 * 输出：true
 * 解释：挑选数字 5 和 7。
 * 5*3 + 7*(-2) = 1
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums = [29,6,10]
 * 输出：true
 * 解释：挑选数字 29, 6 和 10。
 * 29*1 + 6*(-3) + 10*(-1) = 1
 * 
 * 
 * 示例 3：
 * 
 * 输入：nums = [3,6]
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 
 * 
 */

// @lc code=start
class Solution {
    public boolean isGoodArray(int[] nums) {
        int divisor = nums[0];
        for (int num : nums)
        {
            divisor = gcd(divisor, num);
            if(divisor == 1)
                break;
        }
        return divisor == 1;
    }
    public int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
}
// @lc code=end

