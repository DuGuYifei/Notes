#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1020 lang=cpp
 *
 * [1020] 飞地的数量
 */

// @lc code=start
class Solution
{
public:
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int m, n;
    int numEnclaves(vector<vector<int>> &grid)
    {
        m = grid.size() - 1;
        n = grid[0].size() - 1;
        int i = 0;
        while (i <= n)
        {
            if (grid[0][i] == 1)
                dfs(0, i, grid);
            if (grid[m][i] == 1)
                dfs(m, i, grid);
            i++;
        }
        i = 1;
        while (i < m)
        {
            if (grid[i][0] == 1)
                dfs(i, 0, grid);
            if (grid[i][n] == 1)
                dfs(i, n, grid);
            i++;
        }
        int ans = 0;
        for (i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++)
            {
                if (grid[i][j] == 1)
                    ans++;
            }
        return ans;
    }

    void dfs(int x, int y, vector<vector<int>> &grid)
    {
        if (grid[x][y] == 0)
        {
            return;
        }
        grid[x][y] = 0;
        for (auto &i : dirs)
        {
            int nx = x + i[0];
            int ny = y + i[1];
            if (nx >= 0 && nx <= m && ny >= 0 && ny <= n)
                dfs(nx, ny, grid);
        }
    }
};
// @lc code=end
