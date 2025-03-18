#include<vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        // for (int index = nums.size() - 1; index > 0; index--)
        // {
        //     for (int i = 0; i < index; i++)
        //     {
        //         if (nums[i] + nums[index] == target)
        //         {
        //             return {index,i};
        //         }
        //     }
        // }
        // return {};

        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); i++)
        {
            auto iteration = hashtable.find(target - nums[i]);
            if (iteration == hashtable.end())
            {
                hashtable[nums[i]] = i;
            }
            else
                return {i, iteration->second};
        }
        return {};
    }
};
// @lc code=end
