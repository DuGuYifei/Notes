#include<string>
#include<vector>
#include<unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=828 lang=cpp
 *
 * [828] 统计子串中的唯一字符
 */

// @lc code=start
class Solution {
public:
    int uniqueLetterString(string s) {
        int ans = 0;
        unordered_map<char, vector<int>> idxs;
        int n = s.size();
        for(int i = 0; i < n; i++)
        {
            idxs[s[i]].push_back(i);
        }
        for(auto&& [_,v] : idxs)
        {
            v.push_back(n);
            ans += (v[0] + 1) * (v[1] - v[0]);
            for(int i = 1; i < v.size() - 1; i++)
            {
                ans += (v[i] - v[i-1]) * (v[i+1] - v[i]);
            }
        }
        return ans;
    }
};
// @lc code=end

