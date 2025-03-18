#include <vector>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=2100 lang=cpp
 *
 * [2100] 适合打劫银行的日子
 */

// @lc code=start
class Solution
{
public:
    vector<int> right;
    vector<int> goodDaysToRobBank(vector<int> &security, int time)
    {
        if (time == 0)
        {
            iota(security.begin(),security.end(),0);
            return security;
        }
        int n = security.size();
        int count = 0;
        int i = 1;
        vector<int> ans;
        //只需要记录右半边即可，左半边直接在遍历时就count得到
        right = vector<int>(n, -1);
        right[0] = 0;
        while (i < n)
        {
            if (security[i] <= security[i - 1])
            {
                count++;
            }
            else
            {
                count = 0;
            }
            if (count >= time)
            {
                int j = i + time;
                if (j >= n)
                    return ans;

                int r = getRightTime(j, security);
                if (r >= time)
                {
                    ans.push_back(i);
                }
            }
            i++;
        }
        return ans;
    }

    int getRightTime(int target, vector<int> &security)
    {
        if (right[target] != -1)
        {
            return right[target];
        }
        int l = getRightTime(target - 1, security);
        if (security[target] >= security[target - 1])
            right[target] = l + 1;
        else
            right[target] = 0;
        return right[target];
    }
};
// @lc code=end
