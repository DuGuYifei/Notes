#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=1380 lang=cpp
 *
 * [1380] 矩阵中的幸运数
 */

// @lc code=start
class Solution
{
public:
    vector<int> luckyNumbers(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        unordered_map<int, int> colMax;
        vector<int> ans;
        for (int i = 0; i < m; i++)
        {
            int rowmin = matrix[i][0];
            int col = 0;
            for (int j = 1; j < n; j++)
            {
                if (matrix[i][j] < rowmin)
                {
                    rowmin = matrix[i][j];
                    col = j;
                }
            }
            if (colMax[col] == 0)
            {
                int colm = 0;
                for (int j = 0; j < m; j++)
                {
                    if (matrix[j][col] > colm)
                    {
                        colm = matrix[j][col];
                    }
                }
                colMax[col] = colm;
            }
            if (colMax[col] == matrix[i][col])
                ans.push_back(colMax[col]);
        }
        return ans;
    }
};
// @lc code=end
