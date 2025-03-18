#include <string>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */

// @lc code=start
class Solution
{
public:
    unordered_map<char, int> alphabet = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};
    int romanToInt(string s)
    {
        int res = alphabet[s[0]];
        for (int i = 1; i < s.size(); i++)
        {
            if (alphabet[s[i]] > alphabet[s[i - 1]])
            {
                res -= (alphabet[s[i - 1]] * 2 - alphabet[s[i]]);
            }
            else
                res = res + alphabet[s[i]];
        }
        return res;
    }
};
// @lc code=end
