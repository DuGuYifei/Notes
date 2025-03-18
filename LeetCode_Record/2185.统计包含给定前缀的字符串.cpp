#include<vector>
#include<string>
using namespace std;
/*
 * @lc app=leetcode.cn id=2185 lang=cpp
 *
 * [2185] 统计包含给定前缀的字符串
 *
 * https://leetcode-cn.com/problems/counting-words-with-a-given-prefix/description/
 *
 * algorithms
 * Easy (79.05%)
 * Likes:    12
 * Dislikes: 0
 * Total Accepted:    14.3K
 * Total Submissions: 18.1K
 * Testcase Example:  '["pay","attention","practice","attend"]\n"at"'
 *
 * 给你一个字符串数组 words 和一个字符串 pref 。
 * 
 * 返回 words 中以 pref 作为 前缀 的字符串的数目。
 * 
 * 字符串 s 的 前缀 就是  s 的任一前导连续字符串。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：words = ["pay","attention","practice","attend"], pref = "at"
 * 输出：2
 * 解释：以 "at" 作为前缀的字符串有两个，分别是："attention" 和 "attend" 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：words = ["leetcode","win","loops","success"], pref = "code"
 * 输出：0
 * 解释：不存在以 "code" 作为前缀的字符串。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= words.length <= 100
 * 1 <= words[i].length, pref.length <= 100
 * words[i] 和 pref 由小写英文字母组成
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int n = pref.size();
        int ans = 0;
        for(auto& i : words){
            // if(i._Starts_with(pref)){
            //     ans++;
            // }
            if(i.compare(0, n, pref) == 0)
                ans++;
            // ans++;
            // if(i.size() < n)
            //     ans--;
            // else
            //     for(int id = 0; id < n; id++){
            //         if(i[id] != pref[id]){
            //             ans--;
            //             break;
            //         }
            //     }
        }        
        return ans;
    }
};
// @lc code=end

