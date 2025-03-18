#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1414 lang=cpp
 *
 * [1414] 和为 K 的最少斐波那契数字数目
 */

// @lc code=start
class Solution
{
public:
    int findMinFibonacciNumbers(int k)
    {
        if (k == 1)
            return 1;
        vector<int> f{1, 1};
        int i = 1;
        while (f[i] + f[i - 1] <= k)
        {
            f.push_back(f[i] + f[i - 1]);
            i++;
        }
        int sum = 0, ans = 0;
        while (true)
        {
            if (sum + f[i] < k)
            {
                sum = sum + f[i];
                ans++;
                i--;
            }
            else if (sum + f[i] > k)
            {
                i--;
            }
            else
            {
                ans++;
                break;
            }
        }
        return ans;
    }
};
// @lc code=end
