/*
 * @lc app=leetcode.cn id=2373 lang=cpp
 *
 * [2373] 矩阵中的局部最大值
 *
 * https://leetcode.cn/problems/largest-local-values-in-a-matrix/description/
 *
 * algorithms
 * Easy (84.76%)
 * Likes:    26
 * Dislikes: 0
 * Total Accepted:    12.8K
 * Total Submissions: 15K
 * Testcase Example:  '[[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]'
 *
 * 给你一个大小为 n x n 的整数矩阵 grid 。
 * 
 * 生成一个大小为 (n - 2) x (n - 2) 的整数矩阵  maxLocal ，并满足：
 * 
 * 
 * maxLocal[i][j] 等于 grid 中以 i + 1 行和 j + 1 列为中心的 3 x 3 矩阵中的 最大值 。
 * 
 * 
 * 换句话说，我们希望找出 grid 中每个 3 x 3 矩阵中的最大值。
 * 
 * 返回生成的矩阵。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
 * 输出：[[9,9],[8,6]]
 * 解释：原矩阵和生成的矩阵如上图所示。
 * 注意，生成的矩阵中，每个值都对应 grid 中一个相接的 3 x 3 矩阵的最大值。
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
 * 输出：[[2,2,2],[2,2,2],[2,2,2]]
 * 解释：注意，2 包含在 grid 中每个 3 x 3 的矩阵中。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == grid.length == grid[i].length
 * 3 <= n <= 100
 * 1 <= grid[i][j] <= 100
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n = grid.size() - 1;
        vector<vector<int>> ans(n - 1, vector<int>(n - 1));
        for(int i = 1; i < n; i++)
            for(int j = 1; j < n; j++)
            {
                int maximum = 0;
                for(int dx = -1; dx < 2; dx++)
                    for(int dy = -1; dy < 2; dy++)
                    {
                        maximum = max(maximum, grid[i + dx][j + dy]);
                    }
                ans[i - 1][j - 1] = maximum;
            }
        return ans;
    }
};
// @lc code=end

