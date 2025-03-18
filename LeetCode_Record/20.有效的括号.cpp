#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution
{
public:
    bool isValid(string s)
    {
        int n = s.size();
        if (n % 2 != 0)
            return false;
        vector<char> m = {s[0]};
        for (int i = 1; i < n; i++)
        {
            if (m.size() == 0 && (s[i] == ')' || s[i] == ']' || s[i] == '}'))
                return false;
            else if (m.size() != 0 && (s[i] == m.back() + 1 || s[i] == m.back() + 2))
            {
                while (i < n && m.size() > 0)
                {
                    if (s[i] == ')')
                    {
                        if (m.back() == '(')
                        {
                            m.pop_back();
                            i++;
                        }
                        else
                            break;
                    }
                    else
                    {
                        if (m.back() + 2 == s[i])
                        {
                            m.pop_back();
                            i++;
                        }
                        else
                            break;
                    }
                }
                i--;
            }
            else
                m.emplace_back(s[i]);
        }
        return !m.size();
    }
};
// @lc code=end
