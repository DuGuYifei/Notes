#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if(strs.size() ==1)
            return strs[0];
        string s = "";
        for (int j = 0; j < strs[0].size(); j++)
            for (int i = 1; i < strs.size(); i++)
            {
                if (j == strs[i].size() || strs[i][j] != strs[0][j])
                    return s;

                if (strs[i][j] == strs[0][j] && i == strs.size() - 1)
                {
                    s.append(1, strs[0][j]);
                }
            }
        return s;
    }
};
// @lc code=end
