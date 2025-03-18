#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1672 lang=cpp
 *
 * [1672] 最富有客户的资产总量
 */

// @lc code=start
class Solution
{
public:
    int maximumWealth(vector<vector<int>> &accounts)
    {
        int max = 0;
        int n = accounts[0].size();
        for (int i = 0; i < accounts.size(); i++)
        {
            int sum = 0;
            for (int j = 0; j < n; j++)
            {
                sum += accounts[i][j];
            }
            if (sum > max)
            {
                max = sum;
            }
        }
        return max;
    }
};
// @lc code=end
