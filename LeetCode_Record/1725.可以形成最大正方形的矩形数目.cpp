#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1725 lang=cpp
 *
 * [1725] 可以形成最大正方形的矩形数目
 */

// @lc code=start
class Solution
{
public:
    int countGoodRectangles(vector<vector<int>> &rectangles)
    {
        int maxL = 1, ans = 0;
        for (const auto &i : rectangles)
        {
            int side = min(i[0], i[1]);
            if (side > maxL)
            {
                ans = 1;
                maxL = side;
            }
            else if(side == maxL)
            {
                ans++;
            }
        }
        return ans;
    }
};
// @lc code=end
