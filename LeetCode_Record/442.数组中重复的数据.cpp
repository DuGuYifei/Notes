#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=442 lang=cpp
 *
 * [442] 数组中重复的数据
 */

// @lc code=start
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        // int n = nums.size();
        // vector<int> number(n + 1,0);
        // vector<int> ans;
        // for(int& i : nums)
        // {
        //     if(number[i] == 1)
        //     {
        //         ans.push_back(i);
        //     }
        //     number[i]++;
        // }
        // return ans;

        vector<int> ans;
        for(auto&i : nums)
        {
            int num = abs(i);
            if(nums[num - 1] <0)
                ans.push_back(num);
            else
                nums[num - 1]*=-1;
        }
        return ans;
    }
};
// @lc code=end

