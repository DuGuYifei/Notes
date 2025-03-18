#include <vector>
#include <initializer_list>
using namespace std;
/*
 * @lc app=leetcode.cn id=688 lang=cpp
 *
 * [688] “马”在棋盘上的概率
 */

// @lc code=start
// class Solution
// {
//     int dirs[8][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
//     //double rate = 0;
//     double dp[25][25][101];
// public:
//     double knightProbability(int n, int k, int row, int column)
//     {
//         //vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(k + 1)));
//         // k+1即多出一位是因为用起始记录答案，随后以为k=0时是不剩步数时不出去概率为1
//         dfs(n, k, row, column);
//         // return rate;
//         return dp[row][column][k];
//     }

//     //void dfs(int n, int k, int row, int column, vector<vector<vector<double>>> &dp)
//     void dfs(int n, int k, int row, int column)
//     {
//         if (k > 0)
//         {
//             for (const int &i : {0, 1, 2, 3, 4, 5, 6, 7})
//             {
//                 int x = row + dirs[i][0];
//                 int y = column + dirs[i][1];
//                 int next = k - 1;

//                 if (x > -1 && x < n && y > -1 && y < n)
//                 {
//                     if (dp[x][y][next] != 0)
//                     {
//                         dp[row][column][k] += dp[x][y][next] * 0.125;
//                         continue;
//                     }
//                     dfs(n, next, x, y);
//                     dp[row][column][k] += dp[x][y][next] * 0.125;
//                 }
//             }
//         }
//         else
//             // rate += r;
//             dp[row][column][0] = 1;
//         return;
//     }
// };
class Solution
{
    int dirs[8][2] = {{2, 1}, {2, -1}, {1, 2}, {1, -2}, {-2, 1}, {-2, -1}, {-1, 2}, {-1, -2}};
    double dp[25][25][101];
public:
    double knightProbability(int n, int k, int row, int column)
    {
        dfs(n, k, row, column);
        return dp[row][column][k];
    }
    void dfs(int n, int k, int row, int column)
    {
        if (k > 0)
        {
            for (int i = 0;i < 8;i++)
            {
                int x = row + dirs[i][0];
                int y = column + dirs[i][1];
                int next = k - 1;

                if (x > -1 && x < n && y > -1 && y < n)
                {
                    if (dp[x][y][next] != 0)
                    {
                        dp[row][column][k] += dp[x][y][next] * 0.125;
                        continue;
                    }
                    dfs(n, next, x, y);
                    dp[row][column][k] += dp[x][y][next] * 0.125;
                }
            }
        }
        else
            dp[row][column][0] = 1;
        return;
    }
};
// @lc code=end
