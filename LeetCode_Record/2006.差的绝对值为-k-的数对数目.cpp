#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=2006 lang=cpp
 *
 * [2006] 差的绝对值为 K 的数对数目
 */

// @lc code=start
class Solution
{
public:
    int countKDifference(vector<int> &nums, int k)
    {
        int n = nums.size();
        int ans = 0;
        unordered_map<int, int> num;
        for (int i = 0; i < n; i++)
        {
            ans += num[nums[i] + k];
            ans += num[nums[i] - k];
            num[nums[i]]++;
        }
        // for (int i = 0; i < n - 1; i++)
        // {
        //     int need1 = nums[i] - k;
        //     int need2 = nums[i] + k;
        //     for (int j = i + 1; j < n; j++)
        //     {
        //         if (nums[j] == need1 || nums[j] == need2)
        //             ans++;
        //     }
        // }
        return ans;
    }
};
// @lc code=end
