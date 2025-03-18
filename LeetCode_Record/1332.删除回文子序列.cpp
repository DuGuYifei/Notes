#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1332 lang=cpp
 *
 * [1332] 删除回文子序列
 */

// @lc code=start
class Solution
{
public:
    int removePalindromeSub(string s)
    {
        int n = s.size();
        for (int i = 0; i < n >> 1; i++)
        {
            if (s[i] != s[n - i - 1])
            {
                return 2;
            }
        }
        return 1;
    }
};
// @lc code=end
