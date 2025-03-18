/*
 * @lc app=leetcode.cn id=2180 lang=cpp
 *
 * [2180] 统计各位数字之和为偶数的整数个数
 *
 * https://leetcode-cn.com/problems/count-integers-with-even-digit-sum/description/
 *
 * algorithms
 * Easy (65.01%)
 * Likes:    17
 * Dislikes: 0
 * Total Accepted:    12.6K
 * Total Submissions: 19.1K
 * Testcase Example:  '4'
 *
 * 给你一个正整数 num ，请你统计并返回 小于或等于 num 且各位数字之和为 偶数 的正整数的数目。
 * 
 * 正整数的 各位数字之和 是其所有位上的对应数字相加的结果。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：num = 4
 * 输出：2
 * 解释：
 * 只有 2 和 4 满足小于等于 4 且各位数字之和为偶数。    
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：num = 30
 * 输出：14
 * 解释：
 * 只有 14 个整数满足小于等于 30 且各位数字之和为偶数，分别是： 
 * 2、4、6、8、11、13、15、17、19、20、22、24、26 和 28 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= num <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int countEven(int num) {
        if(num == 1000) return countEven(999);
        int t = num/10;
        return (t * 5 - 1) + (t > 9 ? (num - t * 10 + 1 + (t + (num/100 + 1) % 2) % 2) / 2 : (num - t * 10 + 1 + (t + 1) % 2) / 2);
    }
};
// @lc code=end

