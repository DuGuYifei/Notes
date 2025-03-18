#include <vector>
//#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=1791 lang=cpp
 *
 * [1791] 找出星型图的中心节点
 */

// @lc code=start
class Solution
{
public:
    int findCenter(vector<vector<int>> &edges)
    {
        // unordered_map<int, int> v_e;
        // for (auto &i : edges)
        // {
        //     v_e[i[0]]++;
        //     if (v_e[i[0]] > 1)
        //         return i[0];
        //     v_e[i[1]]++;
        //     if (v_e[i[1]] > 1)
        //         return i[1];
        // }
        // return 0;
        return edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1] ? edges[0][0]:edges[0][1];
    }
};
// @lc code=end
