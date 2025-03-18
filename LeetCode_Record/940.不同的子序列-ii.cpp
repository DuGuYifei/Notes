#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=940 lang=cpp
 *
 * [940] 不同的子序列 II
 */

// @lc code=start
class Solution
{
public:
    // 一定要先写几个例子，得到规律，写状态转移函数
    int distinctSubseqII(string s)
    {
        int haveHad[26]{0};
        int mod = 10e9 + 7;
        int ans = 1; // 空集
        for (auto &i : s)
        {
            int newCount = ans;
            ans = ((ans + newCount - haveHad[i - 'a']) % mod + mod) % mod;
            haveHad[i - 'a'] = newCount; // 这样自动将重复的给覆盖了，因为newCount包含了重复的部分即前面有的里面都有
        }
        return ans - 1;
    }
};
// @lc code=end
