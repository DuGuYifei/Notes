#include <algorithm>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1608 lang=cpp
 *
 * [1608] 特殊数组的特征值
 */

// @lc code=start
class Solution {
public:
    int specialArray(vector<int>& nums) {
        sort(nums.begin(),nums.end(),[](const int&a, const int&b){return a>b;});
        int n = nums.size();
        for(int i = 1; i < n; i++)
        {
            if(i <= nums[i-1])
            {
                if(i > nums[i])
                    return i;
            }
            else
                return -1;
        }
        if(n <= nums.back())
        {
            return n;
        }
        return -1;
    }
};
// @lc code=end

