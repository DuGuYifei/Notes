#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=777 lang=cpp
 *
 * [777] 在LR字符串中交换相邻字符
 */

// @lc code=start
class Solution
{
public:
    bool canTransform(string start, string end)
    {
        int n = start.size();
        for (int i = 0; i < n; i++)
        {
            char e = end[i];
            char s = start[i];
            if (s != e)
            {
                if (e == 'L' && s == 'X')
                {
                    int lcnt = 1;
                    while (lcnt > 0)
                    {
                        i++;
                        if (i == n || end[i] == 'R')
                            return false;
                        if (end[i] == 'L')
                            lcnt++;
                        if (start[i] == 'L')
                            lcnt--;
                    }
                }
                else if (s == 'R' && e == 'X')
                {
                    int rcnt = 1;
                    while (rcnt > 0)
                    {
                        i++;
                        if (i == n || start[i] == 'L')
                            return false;
                        if (start[i] == 'R')
                            rcnt++;
                        if (end[i] == 'R')
                            rcnt--;
                    }
                }
                else
                    return false;
            }
        }
        return true;
    }
};
// @lc code=end
