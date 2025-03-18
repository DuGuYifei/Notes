#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1185 lang=cpp
 *
 * [1185] 一周中的第几天
 */

// @lc code=start
class Solution
{
public:
    string dayOfTheWeek(int day, int month, int year)
    {
        string week[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        int monthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days = (year - 1971) * 365 + (year - 1969) / 4;
        for (int i = 0; i < month - 1; i++)
        {
            days += monthDay[i];
        }

        if ((year % 400 == 0 || year % 4 == 0 && year % 100 != 0) && month > 2)
            days += 1;

        days += day;

        return week[(days + 3) % 7];
    }
};
// @lc code=end
