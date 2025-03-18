#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1189 lang=cpp
 *
 * [1189] “气球” 的最大数量
 */

// @lc code=start
class Solution
{
public:
    int maxNumberOfBalloons(string text)
    {
        int b = 0, a = 0, l = 0, o = 0, n = 0;
        for (char &i : text)
        {
            switch (i)
            {
            case 'b':
                b++;
                break;
            case 'a':
                a++;
                break;
            case 'l':
                l++;
                break;
            case 'o':
                o++;
                break;
            case 'n':
                n++;
                break;
            }
        }
        l /= 2;
        o /= 2;
        return min({b, a, l, o, n});
    }
};
// @lc code=end
