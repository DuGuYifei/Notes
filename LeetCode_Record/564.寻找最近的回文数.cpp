#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=564 lang=cpp
 *
 * [564] 寻找最近的回文数
 */

// @lc code=start
class Solution
{
public:
    string nearestPalindromic(string n)
    {
        int size = n.size() - 1;
        if (size == 0)
        {
            n = n[0] - 1;
            return n;
        }
        else if (n == "11")
            return "9";

        long nn = stol(n);
        if (nn == pow(10, size))
            return to_string(nn - 1);
        if (nn - 1 == pow(10, size))
            return to_string(nn - 2);
        if (nn + 1 == pow(10, size + 1))
            return to_string(nn + 2);

        int i = size;
        for (; i >= (size + 1) >> 1; i--)
        {
            n[i] = n[size - i];
        }
        i++;
        long a = stol(n);
        bool nine =  n[i] != '9';
        long c;
        if (size % 2 != 0 || size == 1)
        {

            n[i] -= 1;
            n[i - 1] -= 1;
            c = stol(n);
            if (nine)
            {
                n[i] += 2;
                n[i - 1] += 2;
            }
        }
        else
        {
            n[i] -= 1;
            c = stol(n);
            if (nine)
            {
                n[i] += 2;
            }
        }

        
        long b = stol(n);
        if (a == nn)
        {
            a = b;
            if(a==nn)
            return to_string(c);
        }

        if (nine && abs(a - nn) > b - nn)
        {
            a = b;
        }
        if (abs(a - nn) >= nn - c)
        {
            return to_string(c);
        }
        return to_string(a);
    }
};
// @lc code=end
