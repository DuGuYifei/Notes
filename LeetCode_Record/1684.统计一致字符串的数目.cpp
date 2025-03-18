#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1684 lang=cpp
 *
 * [1684] 统计一致字符串的数目
 *
 * https://leetcode-cn.com/problems/count-the-number-of-consistent-strings/description/
 *
 * algorithms
 * Easy (82.46%)
 * Likes:    40
 * Dislikes: 0
 * Total Accepted:    27K
 * Total Submissions: 32.6K
 * Testcase Example:  '"ab"\n["ad","bd","aaab","baa","badab"]'
 *
 * 给你一个由不同字符组成的字符串 allowed 和一个字符串数组 words 。如果一个字符串的每一个字符都在 allowed 中，就称这个字符串是
 * 一致字符串 。
 * 
 * 请你返回 words 数组中 一致字符串 的数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
 * 输出：2
 * 解释：字符串 "aaab" 和 "baa" 都是一致字符串，因为它们只包含字符 'a' 和 'b' 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
 * 输出：7
 * 解释：所有字符串都是一致的。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
 * 输出：4
 * 解释：字符串 "cc"，"acd"，"ac" 和 "d" 是一致字符串。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * 1 
 * allowed 中的字符 互不相同 。
 * words[i] 和 allowed 只包含小写英文字母。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        // //方法一
        // unordered_set<char> as;
        // int ans = 0;
        // for(auto& i : allowed)
        //     as.insert(i);
        // for(auto& i : words)
        // {
        //     ans++;
        //     for(auto&j : i)
        //         if(!as.count(j))
        //         {
        //             ans--;
        //             break;
        //         }
        // }
        // return ans;

        // 方法二
        int mask = 0;
        for (auto c : allowed) {
            mask |= 1 << (c - 'a');
        }
        int res = 0;
        for (auto &&word : words) {
            int mask1 = 0;
            for (auto c : word) {
                mask1 |= 1 << (c - 'a');
            }
            if ((mask1 | mask) == mask) {
                res++;
            }
        }
        return res;
    }
};
// @lc code=end

