#include <unordered_map>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1072 lang=cpp
 *
 * [1072] 按列翻转得到最大值等行数
 *
 * https://leetcode.cn/problems/flip-columns-for-maximum-number-of-equal-rows/description/
 *
 * algorithms
 * Medium (61.89%)
 * Likes:    77
 * Dislikes: 0
 * Total Accepted:    6.9K
 * Total Submissions: 10.5K
 * Testcase Example:  '[[0,1],[1,1]]'
 *
 * 给定 m x n 矩阵 matrix 。
 * 
 * 你可以从中选出任意数量的列并翻转其上的 每个 单元格。（即翻转后，单元格的值从 0 变成 1，或者从 1 变为 0 。）
 * 
 * 返回 经过一些翻转后，行与行之间所有值都相等的最大行数 。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：matrix = [[0,1],[1,1]]
 * 输出：1
 * 解释：不进行翻转，有 1 行所有值都相等。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：matrix = [[0,1],[1,0]]
 * 输出：2
 * 解释：翻转第一列的值之后，这两行都由相等的值组成。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：matrix = [[0,0,0],[0,0,1],[1,1,0]]
 * 输出：2
 * 解释：翻转前两列的值之后，后两行由相等的值组成。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 300
 * matrix[i][j] == 0 或 1
 * 
 * 
 */

// @lc code=start
struct VectorHash {
    std::size_t operator()(const std::vector<int>& vec) const {
        std::size_t seed = vec.size();
        for (const auto& num : vec) {
            seed ^= std::hash<int>{}(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        
        unordered_map<vector<int>, int, VectorHash> vmap;
        int m = matrix.size();
        int n = matrix[0].size();
        int ans = 0;
        for(int i = 0; i < m; i++){
            vector<int> zeroTemp;
            vector<int> oneTemp;
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 0){
                    zeroTemp.push_back(j);
                }else{
                    oneTemp.push_back(j);
                }
            }
            vmap[zeroTemp]++;
            vmap[oneTemp]++;
            ans = max(ans, vmap[zeroTemp]);
            ans = max(ans, vmap[oneTemp]);
        }
        return ans;
    }
};
// @lc code=end

