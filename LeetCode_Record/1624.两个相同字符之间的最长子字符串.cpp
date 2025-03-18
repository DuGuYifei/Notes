/*
 * @lc app=leetcode.cn id=1624 lang=cpp
 *
 * [1624] 两个相同字符之间的最长子字符串
 */

// @lc code=start
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        //unordered_map<char, int> idx;
        int idx[26] = {0};
        int n = s.size();
        int ans = -1;
        for(int i = 0; i < n; i++)
        {
            int id = s[i] - 'a';
            if(idx[id])
                ans = max(i - idx[id], ans);
            else
                idx[id] = i + 1;
        }
        return ans;
    }
};
// @lc code=end

