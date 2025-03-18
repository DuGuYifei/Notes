#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=504 lang=cpp
 *
 * [504] 七进制数
 */

// @lc code=start
class Solution
{
public:
    string convertToBase7(int num)
    {
        string ans = "";
        bool negative = false;
        if (num < 0)
        {
            negative = true;
            num *= -1;
        }
        while (7 <= num)
        {
            ans = to_string(num % 7) + ans;
            num = num / 7;
        }
        ans = to_string(num) + ans;

        if (negative)
            return "-" + ans;
        return ans;
    }
};
// @lc code=end
