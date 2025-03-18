#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=219 lang=cpp
 *
 * [219] 存在重复元素 II
 */

// @lc code=start
class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        if (!k)
            return false;

        unordered_map<int, int> interval;
        int n = nums.size();
        int size = 0;
        if (k >= n)
        {
            for (int i = 0; i < n; i++)
            {
                interval.emplace(nums[i], i);
                int newsize = interval.size();
                if (newsize == size)
                    return true;
                size = newsize;
            }
            return false;
        }
        for (int i = 0; i < k + 1; i++)
        {
            if (i == n)
            {
                return false;
            }
            interval.emplace(nums[i], i);
            int newsize = interval.size();
            if (newsize == size)
                return true;
            size = newsize;
        }
        for (int i = k + 1; i < n; i++)
        {
            interval.erase(nums[i - k - 1]);
            interval.emplace(nums[i], i);
            int newsize = interval.size();
            if (newsize < size)
                return true;
            size = newsize;
        }
        return false;

        // int leftv = nums[0];
        // int n = nums.size();
        // for (int i = 1; i <= k; i++)
        // {
        //     if (i == n)
        //         return false;
        //     if (nums[i] == leftv)
        //         return true;
        // }
        // int left = 1;
        // for (int i = k + 1; i < n; i++, left++)
        // {
        //     if (nums[i] == nums[left])
        //         return true;
        //     for (int j = left + 1; j < i; j++)
        //     {
        //         if (nums[i] == nums[j])
        //             return true;
        //     }
        // }
        // return false;
    }
};
// @lc code=end
