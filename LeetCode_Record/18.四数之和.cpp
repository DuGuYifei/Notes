#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=18 lang=cpp
 *
 * [18] 四数之和
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        int n = nums.size() - 1;
        if (n < 3)
            return {};
        sort(nums.begin(), nums.end());
        if ((long)nums[0] + nums[1] + nums[2] + nums[3] > target)
            return {};
        if ((long)nums[n] + nums[n - 1] + nums[n - 2] + nums[n - 3] < target)
            return {};
        int first = 0;
        vector<vector<int>> ans;
        while (first < n - 2)
        {
            int second = first + 1;
            while (second < n - 1)
            {
                int sum1 = nums[first] + nums[second];
                int left = second + 1;
                int right = n;
                if ((long)sum1 + nums[left] + nums[left + 1] > target)
                    break;
                while (left != right)
                {
                    if ((long)sum1 + nums[n] + nums[n - 1] < target)
                        break;
                    long sum = (long)sum1 + nums[left] + nums[right];
                    if (sum == target)
                    {
                        ans.push_back({nums[first], nums[second], nums[left], nums[right]});
                        left++;
                        while (left != right && nums[left] == nums[left - 1])
                            left++;
                        if (left != right)
                            right--;
                        while (left != right && nums[right] == nums[right + 1])
                            right--;
                    }
                    else if (sum > target)
                    {
                        right--;
                        while (left != right && nums[right] == nums[right + 1])
                            right--;
                    }
                    else
                    {
                        left++;
                        while (left != right && nums[left] == nums[left - 1])
                            left++;
                    }
                }
                second++;
                while (nums[second] == nums[second - 1] && second < n - 1)
                    second++;
            }
            first++;
            while (nums[first] == nums[first - 1] && first < n - 2)
                first++;
        }
        return ans;
    }
};
// @lc code=end
