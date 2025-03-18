#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=334 lang=cpp
 *
 * [334] 递增的三元子序列
 */

// @lc code=start
class Solution
{
public:
    bool increasingTriplet(vector<int> &nums)
    {
        if (nums.size() < 3)
            return false;
        // int min = nums[0];
        // for (int i = 0; i < n - 2; i++)
        // {
        //     if (i > 0 && nums[i] >= min)
        //     {
        //         continue;
        //     }
        //     min = nums[i];
        //     int val = nums[i];
        //     int number = 1;

        //     for (int j = i + 1; j < n; j++)
        //     {
        //         if (nums[j] > nums[i])
        //         {
        //             if (nums[j] > val)
        //             {
        //                 val = nums[j];
        //                 number++;
        //                 if (number == 3)
        //                     return true;
        //             }
        //             else if (nums[j] < val)
        //             {
        //                 val = nums[j];
        //             }
        //         }
        //     }
        // }

        int first = nums[0], second = INT_MAX;
        for (int i = 1; i < nums.size(); i++)
        {
            // if(nums[i]>second)
            // {
            //     return true;
            // }
            // else if (nums[i] > first)
            // {
            //     second = nums[i];
            // }
            // else if(nums[i]<first)
            // {
            //     first = nums[i];
            // }
            if(nums[i]<=first)
            {
                first = nums[i];
            }
            else if(nums[i]<=second)
            {
                second = nums[i];
            }
            else
                return true;
        }

        return false;
    }
};
// @lc code=end
