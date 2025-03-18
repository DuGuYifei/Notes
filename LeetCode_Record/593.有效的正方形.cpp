#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=593 lang=cpp
 *
 * [593] 有效的正方形
 */

// @lc code=start
class Solution
{
public:
    int getDis(vector<int> &p1, vector<int> &p2)
    {
        return pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2);
    }

    bool validSquare(vector<int> &p1, vector<int> &p2, vector<int> &p3, vector<int> &p4)
    {
        int dis[6]{
            getDis(p1, p2),
            getDis(p1, p3),
            getDis(p1, p4),
            getDis(p2, p3),
            getDis(p2, p4),
            getDis(p3, p4)};
        int a = dis[0], b = -1;
        int anum = 1, bnum = 0;
        int i = 1;
        for (; i < 6; i++)
        {
            if (dis[i] == a)
            {
                anum++;
            }
            else
            {
                b = dis[i];
                bnum = 1;
                i++;
                break;
            }
        }
        while (i < 6)
        {
            if (dis[i] == a)
                anum++;
            else if (dis[i] != b)
                return false;
            else
                bnum++;
            i++;
        }
        if(anum != 4 && bnum != 4 || (!a || !b))
            return false;
        return true;
    }
};
// @lc code=end
