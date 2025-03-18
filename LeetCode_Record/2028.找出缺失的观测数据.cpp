#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2028 lang=cpp
 *
 * [2028] 找出缺失的观测数据
 */

// @lc code=start
class Solution
{
public:
    vector<int> missingRolls(vector<int> &rolls, int mean, int n)
    {
        int m = rolls.size();
        int total = (m + n) * mean;
        int total_m = 0;
        for (const int &i : rolls)
        {
            total_m += i;
        }
        int total_n = total - total_m;
        
        if(total_n < n || total_n > 6 * n)
        {
            return vector<int>();
        }
        else
        {
            int rem = total_n % n;
            int avg = total_n / n;
            vector<int>ans(n, avg);
            if(rem)
            {
                int add = 6-avg;
                int count = rem/add;
                int last = rem - count * add;
                ans[count] += last;
                while(count > 0)
                {
                    count--;
                    ans[count] += add;
                }
            }
            return ans;
        }
    }
};
// @lc code=end
