/*
 * @lc app=leetcode.cn id=1796 lang=java
 *
 * [1796] 字符串中第二大的数字
 *
 * https://leetcode-cn.com/problems/second-largest-digit-in-a-string/description/
 *
 * algorithms
 * Easy (48.86%)
 * Likes:    19
 * Dislikes: 0
 * Total Accepted:    14.6K
 * Total Submissions: 28.8K
 * Testcase Example:  '"dfa12321afd"'
 *
 * 给你一个混合字符串 s ，请你返回 s 中 第二大 的数字，如果不存在第二大的数字，请你返回 -1 。
 * 
 * 混合字符串 由小写英文字母和数字组成。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "dfa12321afd"
 * 输出：2
 * 解释：出现在 s 中的数字包括 [1, 2, 3] 。第二大的数字是 2 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "abc1111"
 * 输出：-1
 * 解释：出现在 s 中的数字只包含 [1] 。没有第二大的数字。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * s 只包含小写英文字母和（或）数字。
 * 
 * 
 */

// @lc code=start
class Solution {
    public int secondHighest(String s) {
        int max1 = -1, max2 = -1;
        int n = s.length();
        for(int i = 0; i < n; i++)
        {
            int num = s.codePointAt(i) - 48;
            if(num < 10)
            {
                if(num > max2)
                {
                    if(num > max1)
                    {
                        max2 = max1;
                        max1 = num;
                    }
                    else if(num != max1)
                        max2 = num;
                }
            }
        }
        return max2;
    }
}
// @lc code=end

