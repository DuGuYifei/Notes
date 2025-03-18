/*
 * @lc app=leetcode.cn id=1031 lang=cpp
 *
 * [1031] 两个非重叠子数组的最大和
 *
 * https://leetcode.cn/problems/maximum-sum-of-two-non-overlapping-subarrays/description/
 *
 * algorithms
 * Medium (59.49%)
 * Likes:    167
 * Dislikes: 0
 * Total Accepted:    10.5K
 * Total Submissions: 17.2K
 * Testcase Example:  '[0,6,5,2,2,5,1,9,4]\n1\n2'
 *
 * 给你一个整数数组 nums 和两个整数 firstLen 和 secondLen，请你找出并返回两个非重叠 子数组 中元素的最大和，长度分别为
 * firstLen 和 secondLen 。
 * 
 * 长度为 firstLen 的子数组可以出现在长为 secondLen 的子数组之前或之后，但二者必须是不重叠的。
 * 
 * 子数组是数组的一个 连续 部分。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
 * 输出：20
 * 解释：子数组的一种选择中，[9] 长度为 1，[6,5] 长度为 2。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
 * 输出：29
 * 解释：子数组的一种选择中，[3,8,1] 长度为 3，[8,9] 长度为 2。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
 * 输出：31
 * 解释：子数组的一种选择中，[5,6,0,9] 长度为 4，[0,3,8] 长度为 3。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= firstLen, secondLen <= 1000
 * 2 <= firstLen + secondLen <= 1000
 * firstLen + secondLen <= nums.length <= 1000
 * 0 <= nums[i] <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        return max(helper(nums, firstLen, secondLen), helper(nums, secondLen, firstLen));
    }

    int helper(vector<int>& nums, int firstLen, int secondLen){
        int n = nums.size();
        int suml = 0, sumr = 0;
        for(int i = 0; i < firstLen; i++){
            suml += nums[i];
        }
        for(int i = firstLen; i < firstLen + secondLen; i++){
            sumr += nums[i];
        }
        int ans = suml + sumr;
        int maxl = suml;
        for(int i = firstLen; i < n - secondLen; i++){
            suml = suml - nums[i - firstLen] + nums[i];
            maxl = max(maxl, suml);
            sumr = sumr - nums[i] + nums[i + secondLen];
            ans = max(ans, maxl + sumr);
        }
        return ans;
    }
};
// @lc code=end

