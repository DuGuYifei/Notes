#include <string>
#include <stack>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1003 lang=cpp
 *
 * [1003] 检查替换后的词是否有效
 *
 * https://leetcode.cn/problems/check-if-word-is-valid-after-substitutions/description/
 *
 * algorithms
 * Medium (58.36%)
 * Likes:    125
 * Dislikes: 0
 * Total Accepted:    32K
 * Total Submissions: 50.3K
 * Testcase Example:  '"aabcbc"'
 *
 * 给你一个字符串 s ，请你判断它是否 有效 。
 * 字符串 s 有效 需要满足：假设开始有一个空字符串 t = "" ，你可以执行 任意次 下述操作将 t 转换为 s ：
 * 
 * 
 * 将字符串 "abc" 插入到 t 中的任意位置。形式上，t 变为 tleft + "abc" + tright，其中 t == tleft +
 * tright 。注意，tleft 和 tright 可能为 空 。
 * 
 * 
 * 如果字符串 s 有效，则返回 true；否则，返回 false。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "aabcbc"
 * 输出：true
 * 解释：
 * "" -> "abc" -> "aabcbc"
 * 因此，"aabcbc" 有效。
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "abcabcababcc"
 * 输出：true
 * 解释：
 * "" -> "abc" -> "abcabc" -> "abcabcabc" -> "abcabcababcc"
 * 因此，"abcabcababcc" 有效。
 * 
 * 示例 3：
 * 
 * 
 * 输入：s = "abccba"
 * 输出：false
 * 解释：执行操作无法得到 "abccba" 。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= s.length <= 2 * 10^4
 * s 由字母 'a'、'b' 和 'c' 组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n % 3 != 0) return false;
        stack<vector<bool>> cnt;
        for(char& c:s){
            if(c == 'a'){
                cnt.push({true,false});
            }else if(c == 'b'){
                if(cnt.empty() || cnt.top()[1]) 
                    return false;
                cnt.top()[1] = true;
            }else{
                if(cnt.empty() || !cnt.top()[1])
                    return false;
                cnt.pop();
            }
        }
        return cnt.empty();
    }
};
// @lc code=end

