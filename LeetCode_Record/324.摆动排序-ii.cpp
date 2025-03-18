#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=324 lang=cpp
 *
 * [324] 摆动排序 II
 */

// @lc code=start
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> order = nums;
        sort(order.begin(),order.end());
        int n = nums.size();
        
        for(int i = 0, j = n - 1, k = n >> 1 - 1; i < n; i += 2, k--,j--)
        {
            nums[i] = order[k];
            if(i + 1 < n)
            {
                nums[i+1] = order[j];
            }
        }
    }
};
// @lc code=end

