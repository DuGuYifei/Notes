#include <vector>
#include <queue>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=784 lang=cpp
 *
 * [784] 字母大小写全排列
 *
 * https://leetcode-cn.com/problems/letter-case-permutation/description/
 *
 * algorithms
 * Medium (69.72%)
 * Likes:    426
 * Dislikes: 0
 * Total Accepted:    75.4K
 * Total Submissions: 106.8K
 * Testcase Example:  '"a1b2"'
 *
 * 给定一个字符串 s ，通过将字符串 s 中的每个字母转变大小写，我们可以获得一个新的字符串。
 * 
 * 返回 所有可能得到的字符串集合 。以 任意顺序 返回输出。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "a1b2"
 * 输出：["a1b2", "a1B2", "A1b2", "A1B2"]
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: s = "3z4"
 * 输出: ["3z4","3Z4"]
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 <= s.length <= 12
 * s 由小写英文字母、大写英文字母和数字组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        ans.push_back("");
        int n = s.size();
        int id = 0;
        while(id < n)
        {
            int an = ans.size();
            if(isdigit(s[id]))
                for(int i = 0; i < an; i++)
                    ans[i].push_back(s[id]);
            else
                for(int i = 0; i < an; i++)
                {
                    ans.push_back(ans[i] + s[id]);
                    ans[i].push_back(s[id] ^ 32);
                }
        }
        return ans;
    }
};
// @lc code=end

