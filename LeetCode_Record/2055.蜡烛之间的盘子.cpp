#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=2055 lang=cpp
 *
 * [2055] 蜡烛之间的盘子
 */

// @lc code=start
class Solution
{
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>> &queries)
    {
        // vector<int> cPos;
        // for (int i = 0; i < s.size(); i++)
        // {
        //     if (s[i] == '|')
        //     {
        //         cPos.push_back(i);
        //     }
        // }
        // int n = cPos.size();
        // vector<int> ans;
        // for (vector<int> &i : queries)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         int left = i[0];
        //         int right = i[1];
        //         int p = 0;
        //         if (cPos[j] >= left)
        //         {
        //             j++;
        //             while (j < n && cPos[j] <= right)
        //             {
        //                 p += cPos[j] - cPos[j - 1] - 1;
        //                 j++;
        //             }
        //             ans.push_back(p);
        //             break;
        //         }
        //     }
        // }
        // return ans;

        // vector<vector<int>> cPos;
        // vector<int> temp = {-1, -1, -1};
        // int ti = 0;
        // for (; ti < s.size(); ti++)
        // {
        //     if (s[ti] == '|')
        //     {
        //         temp[0] = ti;
        //         ti++;
        //         break;
        //     }
        // }
        // for (; ti < s.size(); ti++)
        // {
        //     if (s[ti] == '|')
        //     {
        //         temp[1] = ti;
        //         temp[2] = temp[1] - temp[0] - 1;
        //         if (temp[2] != 0)
        //         {
        //             cPos.push_back(temp);
        //         }
        //         temp[0] = temp[1];
        //         temp[1] = temp[2] = -1;
        //     }
        // }
        // vector<int> ans;
        // for (vector<int> &i : queries)
        // {
        //     int p = 0;
        //     for (vector<int> &j : cPos)
        //     {
        //         if (j[0] >= i[1])
        //         {
        //             break;
        //         }
        //         if (j[0] >= i[0])
        //         {
        //             if (j[1] < i[1])
        //             {
        //                 p += j[2];
        //             }
        //             else if (j[1] == i[1])
        //             {
        //                 p += j[2];
        //                 break;
        //             }
        //             else
        //             {
        //                 break;
        //             }
        //         }
        //     }
        //     ans.push_back(p);
        //     p = 0;
        // }
        // return ans;

        // 提前计算每一个点左侧的蜡烛间盘子数量
        //      和它下一个蜡烛的位置（如果本身就是蜡烛，就是自身位置）
        int n = s.size();
        vector<int> count(n);
        vector<int> nextC(n);
        int c = 0;
        int ct = 0;
        int pos = 0;
        for (; pos < n; pos++)
        {
            count[pos] = 0;
            if (s[pos] == '|')
            {
                pos++;
                break;
            }
        }
        for (; pos < n; pos++)
        {
            if (s[pos] == '|')
            {
                c = ct;
                count[pos] = c;
            }
            else
            {
                count[pos] = c;
                ct++;
            }
        }
        pos--;
        for (int i = n - 1; i > -1; i--)
        {
            if (s[i] == '|')
            {
                pos = i;
            }
            nextC[i] = pos;
        }
        // 开始计算结果
        n = queries.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            int left = nextC[queries[i][0]];
            int right = queries[i][1];
            if (left >= right)
                ans[i] = 0;
            else
                ans[i] = count[right] - count[left];
        }
        return ans;
    }
};
// @lc code=end
