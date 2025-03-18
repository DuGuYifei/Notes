#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1254 lang=cpp
 *
 * [1254] 统计封闭岛屿的数目
 *
 * https://leetcode.cn/problems/number-of-closed-islands/description/
 *
 * algorithms
 * Medium (62.36%)
 * Likes:    216
 * Dislikes: 0
 * Total Accepted:    48.6K
 * Total Submissions: 76.8K
 * Testcase Example:  '[[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]'
 *
 * 二维矩阵 grid 由 0 （土地）和 1 （水）组成。岛是由最大的4个方向连通的 0 组成的群，封闭岛是一个 完全 由1包围（左、上、右、下）的岛。
 * 
 * 请返回 封闭岛屿 的数目。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：grid =
 * [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
 * 输出：2
 * 解释：
 * 灰色区域的岛屿是封闭岛屿，因为这座岛屿完全被水域包围（即被 1 区域包围）。
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
 * 输出：1
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：grid = [[1,1,1,1,1,1,1],
 * [1,0,0,0,0,0,1],
 * [1,0,1,1,1,0,1],
 * [1,0,1,0,1,0,1],
 * [1,0,1,1,1,0,1],
 * [1,0,0,0,0,0,1],
 * ⁠            [1,1,1,1,1,1,1]]
 * 输出：2
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= grid.length, grid[0].length <= 100
 * 0 <= grid[i][j] <=1
 * 
 * 
 */

// @lc code=start
constexpr int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

class Solution {
private:
    vector<vector<int>> visited;
public:
    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        visited = vector<vector<int>>(m, vector<int>(n));
        int res = 0;
        for(int i = 1; i < m - 1; i++) {
            for(int j = 1; j < n - 1; j++) {
                if(grid[i][j] == 0 && visited[i][j] == 0) {
                    res += dfs(grid, i, j);
                }
            }
        }
        return res;
    }

    bool dfs(vector<vector<int>>& grid, int i, int j) {
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
            return false;
        }
        if(grid[i][j] == 1) {
            return true;
        }
        if(visited[i][j] == 1) {
            return true;
        }
        
        visited[i][j] = 1;
        bool res = true;
        for(int k = 0; k < 4; k++) {
            res &= dfs(grid, i + dir[k][0], j + dir[k][1]);
        }
        return res;
    }
};
// @lc code=end

