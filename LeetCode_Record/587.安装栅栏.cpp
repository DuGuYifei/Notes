#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=587 lang=cpp
 *
 * [587] 安装栅栏
 */

// @lc code=start
// class Solution
// {
// public:
//     vector<vector<int>> outerTrees(vector<vector<int>> &trees)
//     {
//         int n = trees.size();
//         if (n <= 3)
//             return trees;
//         // 排序 按 x 值大小 升序, 也要按y同序排序，因为最后几个节点再一列时反向遍历会出现问题
//         sort(trees.begin(), trees.end(), [&](vector<int> a, vector<int> b)
//              { return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1];});
//         vector<vector<int>> ans = {trees[0], trees[1]};
//         // 可以在反向时不用不停find是否已经用过了
//         vector<bool> used(n, false);
//         vector<int> used_index = {0,1};
//         used[1] = true;
//         int indexAns = 1;
//         int x1 = trees[1][0] - trees[0][0];
//         int y1 = trees[1][1] - trees[0][1];
//         for (int i = 2; i < n; i++)
//         {
//             int x2 = trees[i][0] - ans[indexAns][0];
//             int y2 = trees[i][1] - ans[indexAns][1];

//             if (x1 * y2 - x2 * y1 >= 0)
//             {
//                 ans.push_back(trees[i]);
//                 used[i] = true;
//                 used_index.push_back(i);
//                 x1 = x2;
//                 y1 = y2;
//                 indexAns++;
//             }
//             else
//             {
//                 // 将用过的标记搞回来
//                 ans.pop_back();
//                 used[used_index.back()] = false;
//                 used_index.pop_back();
//                 if (indexAns == 1)
//                 {
//                     ans.push_back(trees[i]);
//                     used[i] = true;
//                     used_index.push_back(i);
//                     x1 = trees[i][0] - ans[0][0];
//                     y1 = trees[i][1] - ans[0][1];
//                     continue;
//                 }
//                 indexAns--;
//                 x1 = ans[indexAns][0] - ans[indexAns - 1][0];
//                 y1 = ans[indexAns][1] - ans[indexAns - 1][1];
//                 i--;
//             }
//         }

//         //if (n == indexAns + 1)
//         //   return trees;
//         int i = n - 2;
//         //int leftRightIndex = indexAns;

//         // for (; i >= 0; i--)
//         // {
//         //     if (find(ans.begin(), ans.end(), trees[i]) == ans.end())
//         //     {
//         //         x1 = trees[i][0] - trees[n - 1][0];
//         //         y1 = trees[i][1] - trees[n - 1][1];
//         //         indexAns++;
//         //         ans.push_back(trees[i]);
//         //         i--;
//         //         break;
//         //     }
//         // }
//         // if (i == -1)
//         //     return ans;

//         int x2,y2;
//         for (; i >= 0; i--)
//         {
//             // 判断是否用过
//             if(used[i])
//                 continue;

//             // 判断是否只有一个向量现在
//             if (ans[indexAns] == trees[n-1])
//             {
//                 x1 = trees[i][0] - trees[n-1][0];
//                 y1 = trees[i][1] - trees[n-1][1];
//                 ans.push_back(trees[i]);
//                 indexAns++;
//                 continue;
//             }

//             int x2 = trees[i][0] - ans[indexAns][0];
//             int y2 = trees[i][1] - ans[indexAns][1];

//             if (x1 * y2 - x2 * y1 >= 0)
//             {
//                 ans.push_back(trees[i]);
//                 x1 = x2;
//                 y1 = y2;
//                 indexAns++;
//             }
//             else
//             {
//                 ans.pop_back();
//                 indexAns--;
//                 x1 = ans[indexAns][0] - ans[indexAns - 1][0];
//                 y1 = ans[indexAns][1] - ans[indexAns - 1][1];
//                 i++;
//             }
//         }
//         ans.pop_back();
//         return ans;
//     }
// };
// class Solution
// {
// public:
//     static bool cmp (vector<int>& a, vector<int>& b)
//     {
//         return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1];
//     }
//     vector<vector<int>> outerTrees(vector<vector<int>> &trees)
//     {
//         int n = trees.size();
//         if (n <= 3)
//             return trees;
//         sort(trees.begin(), trees.end(), cmp);
//         vector<vector<int>> ans = {trees[0]};
//         vector<bool> used(n, false);
//         vector<int> used_index = {0};
//         int indexAns = 0;
//         int x1, y1;
//         for (int i = 1; i < n; i++)
//         {
//             if(indexAns == 0)
//             {
//                 x1 = trees[i][0] - trees[0][0];
//                 y1 = trees[i][1] - trees[0][1];
//                 ans.push_back(trees[i]);
//                 used[i] = true;
//                 used_index.push_back(i);
//                 indexAns++;
//                 continue;
//             }

//             int x2 = trees[i][0] - ans[indexAns][0];
//             int y2 = trees[i][1] - ans[indexAns][1];

//             if (x1 * y2 - x2 * y1 >= 0)
//             {
//                 ans.push_back(trees[i]);
//                 used[i] = true;
//                 used_index.push_back(i);
//                 x1 = x2;
//                 y1 = y2;
//                 indexAns++;
//             }
//             else
//             {
//                 ans.pop_back();
//                 used[used_index.back()] = false;
//                 used_index.pop_back();
//                 indexAns--;
//                 i--;
//                 if(indexAns == 0)
//                     continue;
//                 x1 = ans[indexAns][0] - ans[indexAns - 1][0];
//                 y1 = ans[indexAns][1] - ans[indexAns - 1][1];
//             }
//         }

//         int i = n - 2;
//         int x2,y2;
//         for (; i >= 0; i--)
//         {
//             // 判断是否用过
//             if(used[i])
//                 continue;

//             // 判断是否只有一个向量现在
//             if (ans[indexAns] == trees[n-1])
//             {
//                 x1 = trees[i][0] - trees[n-1][0];
//                 y1 = trees[i][1] - trees[n-1][1];
//                 ans.push_back(trees[i]);
//                 indexAns++;
//                 continue;
//             }

//             int x2 = trees[i][0] - ans[indexAns][0];
//             int y2 = trees[i][1] - ans[indexAns][1];

//             if (x1 * y2 - x2 * y1 >= 0)
//             {
//                 ans.push_back(trees[i]);
//                 x1 = x2;
//                 y1 = y2;
//                 indexAns++;
//             }
//             else
//             {
//                 ans.pop_back();
//                 indexAns--;
//                 x1 = ans[indexAns][0] - ans[indexAns - 1][0];
//                 y1 = ans[indexAns][1] - ans[indexAns - 1][1];
//                 i++;
//             }
//         }
//         ans.pop_back();
//         return ans;
//     }
// };
class Solution
{
public:
    static bool cmp(vector<int> &a, vector<int> &b)
    {
        return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1];
    }
    vector<vector<int>> outerTrees(vector<vector<int>> &trees)
    {
        int n = trees.size();
        if (n <= 3)
            return trees;
        sort(trees.begin(), trees.end(), cmp);
        vector<bool> used(n, false);
        vector<int> used_index = {0};
        int x1, y1;
        for (int i = 1; i < n; i++)
        {
            if (used_index.back() == 0)
            {
                x1 = trees[i][0] - trees[0][0];
                y1 = trees[i][1] - trees[0][1];
                used[i] = true;
                used_index.push_back(i);
                continue;
            }

            int x2 = trees[i][0] - trees[used_index.back()][0];
            int y2 = trees[i][1] - trees[used_index.back()][1];

            if (x1 * y2 - x2 * y1 >= 0)
            {
                used[i] = true;
                used_index.push_back(i);
                x1 = x2;
                y1 = y2;
            }
            else
            {
                used[used_index.back()] = false;
                used_index.pop_back();
                i--;
                int j = used_index.back();
                if (j != 0)
                {
                    x1 = trees[j][0] - trees[*(used_index.end() - 2)][0];
                    y1 = trees[j][1] - trees[*(used_index.end() - 2)][1];
                }
            }
        }

        for (int i = n - 2; i >= 0; i--)
        {
            // 判断是否用过
            if (used[i])
                continue;

            // 判断是否只有一个向量现在
            if (used_index.back() == n - 1)
            {
                x1 = trees[i][0] - trees[n - 1][0];
                y1 = trees[i][1] - trees[n - 1][1];
                used_index.push_back(i);
                continue;
            }

            int x2 = trees[i][0] - trees[used_index.back()][0];
            int y2 = trees[i][1] - trees[used_index.back()][1];

            if (x1 * y2 - x2 * y1 >= 0)
            {
                x1 = x2;
                y1 = y2;
                used_index.push_back(i);
            }
            else
            {
                used_index.pop_back();
                int j = used_index.back();
                x1 = trees[j][0] - trees[*(used_index.end() - 2)][0];
                y1 = trees[j][1] - trees[*(used_index.end() - 2)][1];
                i++;
            }
        }
        int nu = used_index.size() - 1;
        vector<vector<int>> ans(nu);
        for (int i = 0; i < nu; i++)
        {
            ans[i] = trees[used_index[i]];
        }
        return ans;
    }
};
// @lc code=end
