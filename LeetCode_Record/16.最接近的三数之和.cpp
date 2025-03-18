#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {

        sort(nums.begin(), nums.end());
        if (target <= nums[0] + nums[1] + nums[2])
            return nums[0] + nums[1] + nums[2];

        int n = nums.size() - 1;

        if (target >= nums[n] + nums[n - 1] + nums[n - 2])
            return nums[n] + nums[n - 1] + nums[n - 2];

        int ans = nums[0] + nums[1] + nums[n];
        for (int i = 0; i < n - 1; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = n;
            while (left != right)
            {
                int temp = nums[i] + nums[left] + nums[right];
                if (temp < target)
                {
                    left++;
                    while (left != right && nums[left] == nums[left - 1])
                    {
                        left++;
                    }
                }
                else if (temp > target)
                {
                    right--;
                    while (left != right && nums[right] == nums[right + 1])
                    {
                        right--;
                    }
                }
                else
                    return target;

                if (abs(ans - target) > abs(temp - target))
                    ans = temp;
            }
        }
        return ans;
    }
};
// @lc code=end
