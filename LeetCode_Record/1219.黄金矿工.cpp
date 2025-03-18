#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=1219 lang=cpp
 *
 * [1219] 黄金矿工
 */

// @lc code=start
class Solution {
public:
    int m,n,ans=0;
    int dirs[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if(grid[i][j]!=0)
                    ans = max(ans,dfs(i, j, grid));
            }
        return ans;
    }
    int dfs(int x, int y, vector<vector<int>>& grid)
    {
        int gold = 0;
        int temp = grid[x][y];
        grid[x][y] = 0;
        for (int i = 0;i<4;i++)
        {
            int nx = x + dirs[i][0], ny = y + dirs[i][1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || grid[nx][ny] == 0)
                continue;
            else
                gold = max(gold,dfs(nx, ny, grid));
        }
        grid[x][y] = temp;
        return gold + grid[x][y];
    }
};
// @lc code=end
