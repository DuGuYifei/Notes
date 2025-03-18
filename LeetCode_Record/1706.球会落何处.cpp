#include <vector>   
using namespace std;
/*
 * @lc app=leetcode.cn id=1706 lang=cpp
 *
 * [1706] 球会落何处
 */

// @lc code=start
class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        vector<int>ans;
        int m = grid.size();
        int n = grid[0].size();

        for(int i = 0;i<n;i++)
        {
            int x = i;
            int y = 0;
            while(y<m)
            {
                if(grid[y][x] == 1)
                {
                    x++;
                    if(x == n || grid[y][x] ==-1)
                    {
                        x = -1;
                        break;
                    }
                }
                else
                {
                    x--;
                    if(x == -1 || grid[y][x] == 1)
                    {
                        x = -1;
                        break;
                    }
                }

                y++;
            }
            ans.push_back(x);
        }
        return ans;
    }
};
// class Solution {
// public:
//     vector<int> findBall(vector<vector<int>>& grid) {
//         vector<int>ans;
//         int m = grid.size();
//         int n = grid[0].size();
//         for(int i = 0;i<n;i++)
//         {
//             int x = i;
//             int y = 0;
//             while(true)
//             {
//                 if(grid[y][x] == 1)
//                 {
//                     x++;
//                     if(x == n || grid[y][x] ==-1)
//                     {
//                         ans.push_back(-1);
//                         break;
//                     }
//                 }
//                 else
//                 {
//                     x--;
//                     if(x == -1 || grid[y][x] == 1)
//                     {
//                         ans.push_back(-1);
//                         break;
//                     }
//                 }
//                 if(++y == m)
//                 {
//                     ans.push_back(x);
//                     break;
//                 }

//             }

//         }
//         return ans;
//     }
// };
// @lc code=end

