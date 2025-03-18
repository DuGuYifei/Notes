#include <limits.h>
/*
 * @lc app=leetcode.cn id=7 lang=cpp
 *
 * [7] 整数反转
 */

// @lc code=start
class Solution
{
public:
    int reverse(int x)
    {
        if (x == 0)
            return 0;
        int origin = x;
        int res = 0;
        while (x != 0)
        {
            if(res < INT_MIN/10|| res > INT_MAX/10)
                return 0;

            int pop = x % 10;
            x = x / 10;

            res = res * 10 + pop;

            //错的：因为10就会直接给0
            // if ((res ^ origin) < 0)
            //     {return 0;}
        }

        return res;
    }
};
// @lc code=end
