#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1163 lang=cpp
 *
 * [1163] 按字典序排在最后的子串
 *
 * https://leetcode.cn/problems/last-substring-in-lexicographical-order/description/
 *
 * algorithms
 * Hard (27.54%)
 * Likes:    89
 * Dislikes: 0
 * Total Accepted:    8.9K
 * Total Submissions: 30.9K
 * Testcase Example:  '"abab"'
 *
 * 给你一个字符串 s ，找出它的所有子串并按字典序排列，返回排在最后的那个子串。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "abab"
 * 输出："bab"
 * 解释：我们可以找出 7 个子串 ["a", "ab", "aba", "abab", "b", "ba", "bab"]。按字典序排在最后的子串是
 * "bab"。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "leetcode"
 * 输出："tcode"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 4 * 10^5
 * s 仅含有小写英文字符。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string lastSubstring(string s) {
        int l = 0, r = 1, k = 0;
        int n = s.size();
        while(r + k < n){
            if(s[l] < s[r + k]){
                l = r + k;
                r = l + 1;
                k = 0;
            }else if(s[l + k] == s[r + k]){
                k++;
            }else if(s[l + k] < s[r + k]){
                l = r;
                r = l + 1;
                k = 0;
            }else{
                r++;
                k = 0;
            }
        }
        return s.substr(l);
    }
};
// @lc code=end

