#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1781 lang=cpp
 *
 * [1781] 所有子字符串美丽值之和
 *
 * https://leetcode-cn.com/problems/sum-of-beauty-of-all-substrings/description/
 *
 * algorithms
 * Medium (53.50%)
 * Likes:    26
 * Dislikes: 0
 * Total Accepted:    6.7K
 * Total Submissions: 11.8K
 * Testcase Example:  '"aabcb"'
 *
 * 一个字符串的 美丽值 定义为：出现频率最高字符与出现频率最低字符的出现次数之差。
 * 
 * 
 * 比方说，"abaacc" 的美丽值为 3 - 1 = 2 。
 * 
 * 
 * 给你一个字符串 s ，请你返回它所有子字符串的 美丽值 之和。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：s = "aabcb"
 * 输出：5
 * 解释：美丽值不为零的字符串包括 ["aab","aabc","aabcb","abcb","bcb"] ，每一个字符串的美丽值都为 1 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：s = "aabcbaa"
 * 输出：17
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * s 只包含小写英文字母。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            vector<int> cnt(26);
            int maxFreq = 0;
            for(int j = i; j < n; j++)
            {
                cnt[s[j] - 'a']++;
                maxFreq = max(maxFreq, cnt[s[j] - 'a']);
                int minFreq = n;
                for(int k = 0; k < 26; k++)
                    if(cnt[k])
                        minFreq = min(minFreq, cnt[k]);
                ans += maxFreq - minFreq;
            }
        }
        return ans;
    }
};
// @lc code=end

