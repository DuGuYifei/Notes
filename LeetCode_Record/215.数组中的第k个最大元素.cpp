#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=215 lang=cpp
 *
 * [215] 数组中的第K个最大元素
 */

// @lc code=start
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums,0,nums.size() - 1, k);
    }

    int quickSelect(vector<int>& nums, int l, int r, int k)
    {
        int amountLeft = setStdVal(nums,l,r) + 1;
        if(amountLeft == k)
            return nums[amountLeft - 1];
        else
            return amountLeft < k? quickSelect(nums,amountLeft,r,k) : quickSelect  (nums,l,amountLeft - 1,k);
    }

    inline int setStdVal(vector<int>& nums, int l, int r)
    {
        int index = (r + l)/2;
        swap(nums[index],nums[r]);
        return partition(nums,l,r);
    }

    inline int partition(vector<int>& nums, int l, int r)
    {
        int stdVal = nums[r];
        int pivot = l;
        for(int i = l;i < r;i++)
        {
            if(nums[i] > stdVal)
            {
                swap(nums[pivot++], nums[i]);
            }
        }
        swap(nums[pivot],nums[r]);
        return pivot;   
    }
};
// @lc code=end

