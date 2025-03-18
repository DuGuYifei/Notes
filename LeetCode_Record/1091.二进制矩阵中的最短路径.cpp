#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=1091 lang=cpp
 *
 * [1091] 二进制矩阵中的最短路径
 *
 * https://leetcode.cn/problems/shortest-path-in-binary-matrix/description/
 *
 * algorithms
 * Medium (38.79%)
 * Likes:    266
 * Dislikes: 0
 * Total Accepted:    63.1K
 * Total Submissions: 162.4K
 * Testcase Example:  '[[0,1],[1,0]]'
 *
 * 给你一个 n x n 的二进制矩阵 grid 中，返回矩阵中最短 畅通路径 的长度。如果不存在这样的路径，返回 -1 。
 * 
 * 二进制矩阵中的 畅通路径 是一条从 左上角 单元格（即，(0, 0)）到 右下角 单元格（即，(n - 1, n -
 * 1)）的路径，该路径同时满足下述要求：
 * 
 * 
 * 路径途经的所有单元格都的值都是 0 。
 * 路径中所有相邻的单元格应当在 8 个方向之一 上连通（即，相邻两单元之间彼此不同且共享一条边或者一个角）。
 * 
 * 
 * 畅通路径的长度 是该路径途经的单元格总数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：grid = [[0,1],[1,0]]
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：grid = [[0,0,0],[1,1,0],[1,1,0]]
 * 输出：4
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：grid = [[1,0,0],[1,1,0],[1,1,0]]
 * 输出：-1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == grid.length
 * n == grid[i].length
 * 1 
 * grid[i][j] 为 0 或 1
 * 
 * 
 */

// @lc code=start
constexpr int directions[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0},{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;
        if(n == 1) return 1;
        vector<vector<bool>> visited(n, vector<bool>(n));
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        visited[0][0] = true;
        int step = 1;
        while(!q.empty()){
            step++;
            int len = q.size();
            while(len--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int i = 0; i < 8; i++){
                    int nx = x + directions[i][0];
                    int ny = y + directions[i][1];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= n || grid[nx][ny] == 1 || visited[nx][ny]) continue;
                    visited[nx][ny] = true;
                    if(nx == n - 1 && ny == n - 1) return step;
                    q.push({nx, ny});
                }
            }
        }
        return -1;
    }
};
// @lc code=end

