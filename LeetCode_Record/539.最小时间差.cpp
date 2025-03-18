#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=539 lang=cpp
 *
 * [539] 最小时间差
 */

// @lc code=start
class Solution
{
public:
    int findMinDifference(vector<string> &timePoints)
    {
        int n = timePoints.size();
        if (n>1440)
        return 0;
        sort(timePoints.begin(), timePoints.end());
        auto minu = [&](string t) -> int
        { return (t[0] - '0') * 10 * 60 + (t[1] - '0') * 60 + (t[3] - '0') * 10 + t[4] - '0'; };
        int res = minu(timePoints[n - 1]) -  minu(timePoints[0]);
        if(res>720) res = 1440-res;
        for (int i = 1; i < timePoints.size(); i++)
        {
            int temp = minu(timePoints[i]) -  minu(timePoints[i-1]);
            if(temp>720)temp = 1440-temp;
            if(temp < res)
            {
                res = temp;
            }
        }
        return res;
    }
};
// @lc code=end
