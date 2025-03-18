#include<vector>
using namespace std;
/*
 * @lc app=leetcode.cn ids=827 lang=cpp
 *
 * [827] 最大人工岛
 */

// @lc code=start
class Solution {
private:
        vector<vector<int>> ids;
        vector<int> nums {0};
        int id = 1;
        int n;
public:
    int largestIsland(vector<vector<int>>& grids) {
        n = grids.size() - 1;
        ids = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
        vector<pair<int,int>> zero;
        int ans = 0;
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <= n; j++)
            {
                if(ids[i][j])
                    continue;
                if(grids[i][j])
                {
                    int num = dfs(i, j, grids);
                    ans = max(ans, num);
                    nums.push_back(num);
                    id++;
                }
                else
                    zero.emplace_back(i,j);
            }
        }
        for(auto& [i,j] : zero)
        {
            int idls[3] = {0};
            int num = 1;
            if(i > 0 && ids[i-1][j])
            {
                idls[0]=ids[i-1][j];
                num += nums[idls[0]];
            }
            if(i < n && ids[i+1][j] && ids[i+1][j] != idls[0])
            {
                idls[1] = ids[i+1][j];
                num += nums[idls[1]];
            }
            if(j > 0 && ids[i][j-1] && ids[i][j-1] != idls[0] && ids[i][j-1] != idls[1])
            {
                idls[2] = ids[i][j-1];
                num += nums[idls[2]];
            }
            if(j < n && ids[i][j+1] && ids[i][j+1] != idls[0] && ids[i][j+1] != idls[1] && ids[i][j+1] != idls[2])
            {
                num += nums[ids[i][j+1]];
            }
            ans = max(ans, num);
        }
        return ans;
    }

    int dfs(int i, int j, vector<vector<int>>& grids)
    {
        int num = 1;
        ids[i][j] = id;
        if(i > 0 && grids[i-1][j] && !ids[i-1][j])
            num += dfs(i-1, j, grids);
        if(i < n && grids[i+1][j] && !ids[i+1][j])
            num += dfs(i+1,j,grids);
        if(j > 0 && grids[i][j - 1] && !ids[i][j-1])
            num += dfs(i, j-1, grids);
        if(j < n && grids[i][j + 1] && !ids[i][j+1])
            num += dfs(i,j+1,grids);
        return num;
    }
};
// @lc code=end

