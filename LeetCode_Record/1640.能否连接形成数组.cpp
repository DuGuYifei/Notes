#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1640 lang=cpp
 *
 * [1640] 能否连接形成数组
 */

// @lc code=start
class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        vector<int> idx(101, -1);
        int t = 0;
        for(int& i : arr)
        {
            idx[i] = t++;
        }
        for(auto& i : pieces)
        {
            if(!(~idx[i[0]]))
                return false;
            int n = i.size();
            for(int j = 1; j < n; j++)
            {
                if(!(~idx[i[j]]))
                    return false;
                if(idx[i[j]] != idx[i[j-1]] + 1)
                    return false;
            }
        }
        return true;
    }
};
// @lc code=end

