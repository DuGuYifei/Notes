#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1252 lang=cpp
 *
 * [1252] 奇数值单元格的数目
 */

// @lc code=start
class Solution
{
public:
    int oddCells(int m, int n, vector<vector<int>> &indices)
    {
        vector<int> row(m, 0);
        vector<int> col(n, 0);
        for (auto &i : indices)
        {
            row[i[0]]++;
            col[i[1]]++;
        }
        int oddr = 0, oddc = 0;
        for (int &i : row)
        {
            if (i % 2)
                oddr++;
        }
        for (int &i : col)
        {
            if (i % 2)
                oddc++;
        }
        return oddr * (n - oddc) + oddc * (m - oddr);
    }
};
// @lc code=end
