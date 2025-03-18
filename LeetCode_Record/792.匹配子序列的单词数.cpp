#include <algorithm>
#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=792 lang=cpp
 *
 * [792] 匹配子序列的单词数
 *
 * https://leetcode-cn.com/problems/number-of-matching-subsequences/description/
 *
 * algorithms
 * Medium (46.85%)
 * Likes:    326
 * Dislikes: 0
 * Total Accepted:    30.8K
 * Total Submissions: 61.3K
 * Testcase Example:  '"abcde"\n["a","bb","acd","ace"]'
 *
 * 给定字符串 s 和字符串数组 words, 返回  words[i] 中是s的子序列的单词个数 。
 * 
 * 字符串的 子序列 是从原始字符串中生成的新字符串，可以从中删去一些字符(可以是none)，而不改变其余字符的相对顺序。
 * 
 * 
 * 例如， “ace” 是 “abcde” 的子序列。
 * 
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: s = "abcde", words = ["a","bb","acd","ace"]
 * 输出: 3
 * 解释: 有三个是 s 的子序列的单词: "a", "acd", "ace"。
 * 
 * 
 * Example 2:
 * 
 * 
 * 输入: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
 * 输出: 2
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * 1 <= s.length <= 5 * 10^4
 * 1 <= words.length <= 5000
 * 1 <= words[i].length <= 50
 * words[i]和 s 都只由小写字母组成。
 * 
 * ​​​​
 */

// @lc code=start
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int id = 0;
        vector<vector<int>> dic(26);
        int ans = 0;
        for(auto& i : s)
            dic[i-'a'].push_back(id++);
        for(auto& word:words)
        {
            int j = -1;
            int pos[26] = {0};
            ans++;
            for(auto& i : word)
            {
                id = i - 'a';
                j = upper_bound(dic[id].begin() + pos[id], dic[id].end(), j) - dic[id].begin();
                if(j == dic[id].size())
                {
                    ans--;
                    break;
                }    
                pos[id] = j;
                j = dic[id][j];
            }
        }
        return ans;
    }
};
// @lc code=end

