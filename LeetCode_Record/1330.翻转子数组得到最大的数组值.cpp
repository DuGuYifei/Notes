#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1330 lang=cpp
 *
 * [1330] 翻转子数组得到最大的数组值
 *
 * https://leetcode.cn/problems/reverse-subarray-to-maximize-array-value/description/
 *
 * algorithms
 * Hard (42.22%)
 * Likes:    84
 * Dislikes: 0
 * Total Accepted:    2.7K
 * Total Submissions: 5.8K
 * Testcase Example:  '[2,3,1,5,4]'
 *
 * 给你一个整数数组 nums 。「数组值」定义为所有满足 0 <= i < nums.length-1 的 |nums[i]-nums[i+1]|
 * 的和。
 * 
 * 你可以选择给定数组的任意子数组，并将该子数组翻转。但你只能执行这个操作 一次 。
 * 
 * 请你找到可行的最大 数组值 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums = [2,3,1,5,4]
 * 输出：10
 * 解释：通过翻转子数组 [3,1,5] ，数组变成 [2,5,1,3,4] ，数组值为 10 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums = [2,4,9,24,2,1,10]
 * 输出：68
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 3*10^4
 * -10^5 <= nums[i] <= 10^5
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size() - 1;
        int sum = abs(nums[0] - nums[1]);
        int maxi = 0;
        for(int i = 1; i < n; i++){
            sum += abs(nums[i] - nums[i + 1]);
            maxi = max(maxi, abs(nums[0] - nums[i + 1]) - abs(nums[i] - nums[i + 1]));
            maxi = max(maxi, abs(nums[n] - nums[i - 1]) - abs(nums[i] - nums[i - 1]));
        }
        int maxi2 = INT_MIN, mini2 = INT_MAX;
        for(int i = 0; i < n; i++){
            maxi2 = max(maxi2, min(nums[i], nums[i + 1]));
            mini2 = min(mini2, max(nums[i], nums[i + 1]));
        }
        return sum + max(maxi, (maxi2 - mini2) * 2);
    }
};
// @lc code=end

