#include <string>
#include <limits>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=8 lang=cpp
 *
 * [8] 字符串转换整数 (atoi)
 */

// @lc code=start
class Solution
{
public:
    int myAtoi(string s)
    {
        int res = 0;
        int sign = 0;
        int i;
        for (i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                continue;
            else if (s[i] == '+' && sign == 0)
            {
                sign = 1;
                i++;
                break;
            }
            else if (s[i] == '-' && sign == 0)
            {
                sign = -1;
                i++;
                break;
            }

            else
            {
                break;
            }
        }
        if (sign == 0)
            sign = 1;
        for (; i < s.size(); i++)
        {

            int med = s[i] - 48;
            if (med >= 0 && med <= 9)
            {
                if (sign < 0)
                {
                    if (res < INT_MIN / 10||INT_MIN - res * 10 > -med)
                        return INT_MIN;
                    res = res * 10 - med;
                }
                else
                {
                    if (res > INT_MAX / 10||INT_MAX - res * 10 < med)
                        return INT_MAX;
                    res = res * 10 + med;
                }
                
            }
            else
                break;
        }
        return res;
    }
};
// @lc code=end
