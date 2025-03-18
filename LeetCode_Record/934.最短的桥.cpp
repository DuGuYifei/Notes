#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=934 lang=cpp
 *
 * [934] 最短的桥
 *
 * https://leetcode-cn.com/problems/shortest-bridge/description/
 *
 * algorithms
 * Medium (47.54%)
 * Likes:    284
 * Dislikes: 0
 * Total Accepted:    40.7K
 * Total Submissions: 83.8K
 * Testcase Example:  '[[0,1],[1,0]]'
 *
 * 给你一个大小为 n x n 的二元矩阵 grid ，其中 1 表示陆地，0 表示水域。
 *
 * 岛 是由四面相连的 1 形成的一个最大组，即不会与非组内的任何其他 1 相连。grid 中 恰好存在两座岛 。
 *
 *
 *
 * 你可以将任意数量的 0 变为 1 ，以使两座岛连接起来，变成 一座岛 。
 *
 * 返回必须翻转的 0 的最小数目。
 *
 *
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：grid = [[0,1],[1,0]]
 * 输出：1
 *
 *
 * 示例 2：
 *
 *
 * 输入：grid = [[0,1,0],[0,0,0],[0,0,1]]
 * 输出：2
 *
 *
 * 示例 3：
 *
 *
 * 输入：grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 * n == grid.length == grid[i].length
 * 2 <= n <= 100
 * grid[i][j] 为 0 或 1
 * grid 中恰有两个岛
 *
 *
 */

// @lc code=start
class Solution
{
public:
    int n;
    void dfs(int x, int y, vector<vector<int>> &grid, queue<pair<int, int>> &qu)
    {
        if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] != 1)
            return;

        qu.emplace(x, y);
        grid[x][y] = -1;
        dfs(x - 1, y, grid, qu);
        dfs(x + 1, y, grid, qu);
        dfs(x, y - 1, grid, qu);
        dfs(x, y + 1, grid, qu);
    }
    int shortestBridge(vector<vector<int>> &grid)
    {
        n = grid.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j])
                {
                    queue<pair<int, int>> qu;
                    dfs(i, j, grid, qu);
                    int step = 0;
                    while (!qu.empty())
                    {
                        int size = qu.size();
                        for (int i = 0; i < size; i++)
                        {
                            auto [x, y] = qu.front();
                            qu.pop();
                            if (x > 0)
                            {
                                if (grid[x - 1][y] == 0)
                                {
                                    qu.emplace(x - 1, y);
                                    grid[x - 1][y] = -1;
                                }
                                else if (grid[x - 1][y] == 1)
                                    return step;
                            }

                            if (x < n - 1)
                            {
                                if (grid[x + 1][y] == 0)
                                {
                                    qu.emplace(x + 1, y);
                                    grid[x + 1][y] = -1;
                                }
                                else if (grid[x + 1][y] == 1)
                                    return step;
                            }
                            if (y > 0)
                            {
                                if (grid[x][y - 1] == 0)
                                {
                                    qu.emplace(x, y - 1);
                                    grid[x][y - 1] = -1;
                                }
                                else if (grid[x][y - 1] == 1)
                                    return step;
                            }
                            if (y < n - 1)
                            {
                                if (grid[x][y + 1] == 0)
                                {
                                    qu.emplace(x, y + 1);
                                    grid[x][y + 1] = -1;
                                }
                                else if (grid[x][y + 1] == 1)
                                    return step;
                            }
                        }
                        step++;
                    }
                }
        return 0;
    }
};
// @lc code=end
