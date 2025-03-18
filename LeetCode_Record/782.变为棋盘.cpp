#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=782 lang=cpp
 *
 * [782] 变为棋盘
 */

// @lc code=start
class Solution
{
public:
    int movesToChessboard(vector<vector<int>> &board)
    {
        int ans = 0;
        int n = board.size();
        int x = 0;
        int rx = 0;
        int count_1r = 0, count_0r = 0;
        int count_1c = 0, count_0c = 0;
        int even_0r = 0, odd_0r = 0;
        int even_0c = 0, odd_0c = 0;

        for (int i = 0; i < n; i++)
        {
            int t = board[0][i];
            if (t)
                count_1r++;
            else
            {
                count_0r++;
                if(i % 2)
                    odd_0r++;
                else
                    even_0r++;
            }
            x = (x << 1) + board[0][i];
            rx = (rx << 1) + (!board[0][i]);
        }

        for (int i = 0; i < n; i++)
        {
            if (board[i][0])
                count_1c++;
            else
            {
                count_0c++;
                if(i % 2)
                    odd_0c++;
                else
                    even_0c++;
            }
        }


        // 比较每行是否一样或是反数字，以及比较数量是否是一半
        //先表示回0，计算正序和反序的数量
        int count_x = 1;
        int count_rx = 0;

        for (int i = 1; i < n; i++)
        {
            int t = 0;
            for (int j = 0; j < n; j++)
            {
                t = (t << 1) + board[i][j];
            }
            if (t == x)
                count_x++;
            else if (t == rx)
                count_rx++;
            else
                return -1;
        }

        if (count_x != n / 2 && count_rx != n / 2)
            return -1;
        
        if (count_1r - count_0r == 0)
        {
            ans = min(odd_0r,even_0r);
        }
        else if (count_1r - count_0r == 1)
        {
            // 1多 -- 1要在偶数索引位 -- 0在奇数索引位 -- 在偶数索引位的0就是错误的
            ans = even_0r;
        }
        else if (count_0r - count_1r == 1)
        {
            ans = odd_0r;
        }
        // 如果数量相差超过1 就失败
        else
            return -1;

        if (count_1c - count_0c == 0)
        {
            ans += min(odd_0c,even_0c);
        }
        else if (count_1c - count_0c == 1)
        {
            ans += even_0c;
        }
        else if (count_0c - count_1c == 1)
        {
            ans += odd_0c;
        }
        return ans;
    }
};
// @lc code=end
