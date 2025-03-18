#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=462 lang=cpp
 *
 * [462] 最少移动次数使数组元素相等 II
 */

// @lc code=start
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        int x = quickSelect(nums,0 , n - 1, n / 2 + 1);
        int ans = 0;
        for(int i = 0;i < n;i++)
        {
            ans += abs(nums[i] - x);
        }
        return ans;
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

