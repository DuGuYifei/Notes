#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=553 lang=cpp
 *
 * [553] 最优除法
 */

// @lc code=start
class Solution
{
public:
    string optimalDivision(vector<int> &nums)
    {
        if (nums.size() == 1)
            return to_string(nums[0]);
        if (nums.size() == 2)
            return to_string(nums[0]) + "/" + to_string(nums[1]);
        string ans = to_string(nums[0]) + "/(" + to_string(nums[1]);
        int i = 2;
        while (i < nums.size())
        {
            ans += "/" + to_string(nums[i]);
            i++;
        }
        ans += ")";
        return ans;
    }
};
// @lc code=end
