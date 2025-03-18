/*
 * @lc app=leetcode.cn id=905 lang=cpp
 *
 * [905] 按奇偶排序数组
 */

// @lc code=start
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = nums.size() - 1;
        for(int i = 0; i < n;i++)
        {
            if(nums[i]%2==1)
            {
                for(;n>i;n--)
                {
                    if(nums[n] %2 == 0)
                    {
                        swap(nums[i],nums[n--]);
                        break;
                    }
                }
            }
        }
        return nums;
    }
};
// @lc code=end

