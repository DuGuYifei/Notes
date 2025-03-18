#include <vector>
#include <algorithm>
using namespace std;

/*
 * @lc app=leetcode.cn id=1996 lang=cpp
 *
 * [1996] 游戏中弱角色的数量
 */

// @lc code=start
class Solution
{
public:
    int numberOfWeakCharacters(vector<vector<int>> &properties)
    {
        // sort(properties.begin(), properties.end(), [](vector<int>& a, vector<int>& b) -> bool
        //      {
        //          //  if (a[0] > b[0])
        //          //      return true;
        //          //  else if (a[0] == b[0])
        //          //  {
        //          //      return (a[1] < b[1]);
        //          //  }
        //          //  return false;
        //          return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
        //      });
        // int maxDef = properties[0][1];
        // int res = 0;
        // // for (int i = 1; i < properties.size(); i++)
        // // {
        // //     int m = properties[i][1];
        // //     if (maxDef > m)
        // //         res++;
        // //     else
        // //         maxDef = m;
        // // }
        // for (auto m : properties)
        // {
        //     if (maxDef > m[1])
        //         res++;
        //     else
        //         maxDef = m[1];
        // }
        // return res;
        sort(properties.begin(), properties.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0]; });
        int maxDef = 1;
        int res = 0;
        for (const auto &m : properties)
        {
            if (maxDef > m[1])
                res++;
            else
                maxDef = m[1];
        }
        return res;
    }
};
// @lc code=end
