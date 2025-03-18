#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=417 lang=cpp
 *
 * [417] 太平洋大西洋水流问题
 */

// @lc code=start
static const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution
{
    //vector<vector<bool>> used;
    vector<vector<bool>> goAtlantic;
    vector<vector<bool>> goPacific;
    vector<vector<int>> map;
    vector<vector<int>> ans;
    int m, n;

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        m = heights.size() - 1;
        n = heights[0].size() - 1;
        map = heights;
        goAtlantic = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));
        goPacific = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));

        // Atlantic
        for (int i = 0; i < n; i++)
        {
            //used = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));
            dfs(m, i);
        }
        for (int j = 0; j <= m; j++)
        {
            //used = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));
            dfs(j, n);
        }

        // Pacific
        for (int i = 0; i <= n; i++)
        {
            //used = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));

            dfs_p(0, i);
        }
        for (int j = 1; j <= m; j++)
        {
            //used = vector<vector<bool>>(m + 1, vector<bool>(n + 1, false));

            dfs_p(j, 0);
        }
        return ans;
    }

    void dfs(int x, int y)
    {
        if (
            //used[x][y] || 
            goAtlantic[x][y])
            return;
        goAtlantic[x][y] = true;
        //used[x][y] = true;
        int origin = map[x][y];
        for (auto &[i, j] : dirs)
        {
            int xx = x + i;
            int yy = y + j;

            if (xx > m || xx < 0 || yy > n || yy < 0)
            {
                continue;
            }

            if (map[xx][yy] >= origin)
            {
                dfs(xx, yy);
            }
        }
    }

    void dfs_p(int x, int y)
    {
        if (
            //used[x][y] || 
            goPacific[x][y])
            return;

        goPacific[x][y] = true;
        //used[x][y] = true;
        int origin = map[x][y];

        if (goAtlantic[x][y])
        {
            ans.push_back({x, y});
        }

        for (auto &[i, j] : dirs)
        {
            int xx = x + i;
            int yy = y + j;

            if (xx > m || xx < 0 || yy > n || yy < 0)
            {
                continue;
            }
            if (map[xx][yy] >= origin)
            {
                dfs_p(xx, yy);
            }
        }
    }
};
// @lc code=end
