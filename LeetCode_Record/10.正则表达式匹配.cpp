#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
class Solution
{
public:
    // bool isMatch(string s, string p)
    // {
    //     return match(s.c_str(), p.c_str());
    // }

    // bool match(const char *s, const char *p)
    // {
    //     if (p[0] == '\0')
    //         return s[0] == '\0';

    //     bool frontMatch = s[0] && (s[0] == p[0] || p[0] == '.');

    //     if (p[1] == '*')
    //     {
    //         return match(s, p + 2) || (frontMatch && match(s + 1, p));
    //     }

    //     return frontMatch && match(s + 1, p + 1);
    // }
    bool isMatch(string s, string p)
    {
        s = " "+s;
        p = " "+p;
        int m = s.size();
        int n = p.size();
    
        // auto match = [&](int i, int j)
        // {
        //     if (i == 0)
        //         return false;
        //     if (p[j-1] == '.')
        //         return true;

        //     return p[j - 1] == s[i - 1];
        // };

        bool f[m + 1][n + 1];
        memset(f, false, (m + 1) * (n + 1));

        //其实就是给个初始状态，这样在下文中，j-1就是实际上才遍历到的第j个
        f[0][0] = true;
        for (int i = 1; i < m + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                if (p[j-1] == '*')
                {
                    if (p[j - 2] == s[i - 1] || p[j-2]=='.')
                    {
                        f[i][j] = f[i - 1][j] || f[i][j-2];
                    }
                    else
                        f[i][j] = f[i][j - 2];
                }
                else
                {
                    if (p[j - 1] == s[i - 1] || p[j-1]=='.')
                    {
                        f[i][j] = f[i - 1][j - 1];
                    }
                }
            }
        }

        return f[m][n];
    }
};
// @lc code=end
