#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=661 lang=cpp
 *
 * [661] 图片平滑器
 */

// @lc code=start
class Solution
{
public:
    int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    vector<vector<int>> imageSmoother(vector<vector<int>> &img)
    {
        int row = img.size();
        int col = img[0].size();
        vector<vector<int>> ans(row, vector<int>(col));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                int sum = img[i][j];
                int count = 1;
                for (auto &[a, b] : dirs)
                {
                    int x = i + a;
                    int y = j + b;
                    if(x<row && x>=0 && y <col && y>=0)
                    {
                        sum += img[x][y];
                        count++;
                    }
                }
                ans[i][j] = sum/count;
            }
        }
        return ans;
    }
};
// @lc code=end
