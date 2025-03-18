#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=540 lang=cpp
 *
 * [540] 有序数组中的单一元素
 */

// @lc code=start
class Solution
{
public:
    int singleNonDuplicate(vector<int> &nums)
    {
        int left = 0, right = nums.size() - 1;
        int mid = (left + right) >> 1;
        while (left < right)
        {
            if (mid % 2 == 0)
            {
                if (nums[mid] == nums[mid + 1])
                {
                    left = mid + 2;
                    
                }
                else if (nums[mid] == nums[mid - 1])
                {
                    right = mid - 2;
                }
                else
                    return nums[mid];
            }
            else
            {
                if (nums[mid] == nums[mid - 1])
                {
                    
                    left = mid+1;
                }
                else if(nums[mid] == nums[mid + 1])
                {
                    right = mid-1;
                }
                else
                    return nums[mid];
            }
            mid = (left + right) >> 1;
        }
        return nums[mid];
    }
};
// @lc code=end
