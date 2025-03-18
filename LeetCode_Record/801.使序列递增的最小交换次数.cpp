#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=801 lang=cpp
 *
 * [801] 使序列递增的最小交换次数
 */

// @lc code=start
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> change(n, 1);
        vector<int> unchange(n, 0);
        for(int i = 1; i < n; i++)
        {
            if(nums1[i] > nums1[i - 1] && nums2[i] > nums2[i-1])
            {
                if(nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1])
                {
                    change[i] = min(change[i - 1], unchange[i - 1]) + 1;
                    unchange[i] = min(change[i - 1], unchange[i - 1]);
                }
                else
                {
                    change[i] = change[i - 1] + 1;
                    unchange[i] = unchange[i - 1];
                }
            }
            else
            {
                change[i] = unchange[i - 1] + 1;
                unchange[i] = change[i - 1];
            }
        }
        return min(change[n - 1], unchange[n-1]);
    }
};
// @lc code=end

