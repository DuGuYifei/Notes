#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=398 lang=cpp
 *
 * [398] 随机数索引
 */

// @lc code=start
class Solution {
public:
    vector<int> nums;
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int ans = 0;
        for(int i = 0, cnt = 0;i < nums.size();i++)
        {
            if(nums[i] == target)
            {
                cnt++;
                if(rand()%cnt == 0)
                // 注意后面得不等于0，所以不能直接return
                    //return i; 错误写法
                    ans = i;
            }
        }
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
// @lc code=end

