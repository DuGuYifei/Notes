#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=1282 lang=cpp
 *
 * [1282] 用户分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        unordered_map<int, vector<int>> q;
        vector<vector<int>> ans;
        for(int i = 0; i < groupSizes.size();i++)
        {
            int size = groupSizes[i];

            if(q[size].size() < size)
            {
                q[size].push_back(i);
                if(q[size].size() == size)
                {
                    ans.push_back(q[size]);
                    q[size] = {};
                }
            }
        }
        return ans;
    }
};
// @lc code=end

