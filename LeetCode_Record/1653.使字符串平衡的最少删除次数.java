/*
 * @lc app=leetcode.cn id=1653 lang=java
 *
 * [1653] 使字符串平衡的最少删除次数
 *
 * https://leetcode.cn/problems/minimum-deletions-to-make-string-balanced/description/
 *
 * algorithms
 * Medium (54.91%)
 * Likes:    53
 * Dislikes: 0
 * Total Accepted:    7.9K
 * Total Submissions: 13.8K
 * Testcase Example:  '"aababbab"'
 *
 * 给你一个字符串 s ，它仅包含字符 'a' 和 'b'​​​​ 。
 * 
 * 你可以删除 s 中任意数目的字符，使得 s 平衡 。当不存在下标对 (i,j) 满足 i < j ，且 s[i] = 'b' 的同时 s[j]= 'a'
 * ，此时认为 s 是 平衡 的。
 * 
 * 请你返回使 s 平衡 的 最少 删除次数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "aababbab"
 * 输出：2
 * 解释：你可以选择以下任意一种方案：
 * 下标从 0 开始，删除第 2 和第 6 个字符（"aababbab" -> "aaabbb"），
 * 下标从 0 开始，删除第 3 和第 6 个字符（"aababbab" -> "aabbbb"）。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "bbaaaaabb"
 * 输出：2
 * 解释：唯一的最优解是删除最前面两个字符。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 10^5
 * s[i] 要么是 'a' 要么是 'b'​ 。​
 * 
 * 
 */

// @lc code=start
class Solution {
    public int minimumDeletions(String s) {
        int n = s.length() - 1;
        if(n == 0)
            return 0;
        int a[] = new int[n + 2];
        int b[] = new int[n + 2];
        int cnta = 0;
        int cntb = 0;
        for(int i = 0; i <= n; i++){
            if(s.charAt(i) == 'b')
                a[i + 1] = ++cntb;
            else
                a[i + 1] = cntb;
            if(s.charAt(n - i) == 'a')
                b[n - i] = ++cnta;
            else
                b[n - i] = cnta;
        }
        int maxSum = 100000;
        for(int i = -1; i <= n; i++){
            int tmp = a[i + 1] + b[i + 1];
            maxSum = Math.min(maxSum, tmp);
        }
        return maxSum;
    }
}
// @lc code=end

