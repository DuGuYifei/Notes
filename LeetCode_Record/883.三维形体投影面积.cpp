#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=883 lang=cpp
 *
 * [883] 三维形体投影面积
 */

// @lc code=start
class Solution
{
public:
    int projectionArea(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int sxy = 0, syz = 0, sxz = 0;
        for (int i = 0; i < n; i++)
        {
            int maxZx = 0, maxZy = 0;
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j])
                {
                    sxy++;
                    maxZx = max(maxZx, grid[i][j]);
                }
                // 不要思考太复杂，直接i和j反过来就行了，但是if grid[i][j]就不适合了
                maxZy = max(maxZy, grid[j][i]);
            }
            sxz += maxZx;
            syz += maxZy;
        }
        return  sxy + sxz + syz;
    }
};
// @lc code=end
