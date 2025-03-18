#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=12 lang=cpp
 *
 * [12] 整数转罗马数字
 */

// @lc code=start
class Solution
{
public:
    string intToRoman(int num)
    {
        char alphabet[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        int value[7] = {1,
                        5,
                        10,
                        50,
                        100,
                        500,
                        1000};

        string res = "";
        for (int i = 6; i >= 0; i -= 2)
        {
            int digit = num / value[i];
            int rest = num % value[i];
            if (digit == 0)
                continue;
            else
            {
                if (digit > 8)
                {
                    res.append(1, alphabet[i]);
                    res.append(1, alphabet[i + 2]);
                }
                else if (digit >= 5)
                {
                    res.append(1, alphabet[i + 1]);
                    res.append(digit - 5, alphabet[i]);
                }
                else if (digit > 3)
                {
                    res.append(1, alphabet[i]);
                    res.append(1, alphabet[i + 1]);
                }
                else
                {
                    res.append(digit, alphabet[i]);
                }
                num -= digit * value[i];
            }
        }
        return res;
    }
};
// @lc code=end
