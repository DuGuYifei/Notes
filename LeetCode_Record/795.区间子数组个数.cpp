#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=795 lang=cpp
 *
 * [795] 区间子数组个数
 *
 * https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/description/
 *
 * algorithms
 * Medium (52.98%)
 * Likes:    324
 * Dislikes: 0
 * Total Accepted:    31.7K
 * Total Submissions: 55K
 * Testcase Example:  '[2,1,4,3]\n2\n3'
 *
 * 给你一个整数数组 nums 和两个整数：left 及 right 。找出 nums 中连续、非空且其中最大元素在范围 [left, right]
 * 内的子数组，并返回满足条件的子数组的个数。
 * 
 * 生成的测试用例保证结果符合 32-bit 整数范围。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [2,1,4,3], left = 2, right = 3
 * 输出：3
 * 解释：满足条件的三个子数组：[2], [2, 1], [3]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [2,9,2,5,6], left = 2, right = 8
 * 输出：7
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^9
 * 0 <= left <= right <= 10^9
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size();
        int last1 = -1, last2 = -1, ans = 0;
        for(int i = 0; i < n; i++)
        {
            if(nums[i] >= left && nums[i] <= right)
                last1 = i;
            else if(nums[i] > right)
            {
                last2 = i;
                last1 = -1;
            }
            if(last1 != -1)
                ans += last1 - last2;
        }
        return ans;
    }
};
// @lc code=end

