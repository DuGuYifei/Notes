#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1653 lang=cpp
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
public:
    int minimumDeletions(string s) {
        int n = s.size();
        if(n == 1)
            return 0;
        int b = 0;
        int a = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == 'b')
                b++;
        }
        int ans = 100000;
        ans = min(ans, b);
        for(int i = n - 1; i > 0; i--){
            if(s[i] == 'a')
                a++;
            else
                b--;
            ans = min(ans, b + a);
        }
        if(s[0] == 'b')
            ans = min(a, ans);
        return ans;
    }
};
// @lc code=end

