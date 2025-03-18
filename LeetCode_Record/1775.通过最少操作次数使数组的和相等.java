/*
 * @lc app=leetcode.cn id=1775 lang=java
 *
 * [1775] 通过最少操作次数使数组的和相等
 *
 * https://leetcode-cn.com/problems/equal-sum-arrays-with-minimum-number-of-operations/description/
 *
 * algorithms
 * Medium (48.06%)
 * Likes:    60
 * Dislikes: 0
 * Total Accepted:    6.9K
 * Total Submissions: 13.7K
 * Testcase Example:  '[1,2,3,4,5,6]\n[1,1,2,2,2,2]'
 *
 * 给你两个长度可能不等的整数数组 nums1 和 nums2 。两个数组中的所有值都在 1 到 6 之间（包含 1 和 6）。
 * 
 * 每次操作中，你可以选择 任意 数组中的任意一个整数，将它变成 1 到 6 之间 任意 的值（包含 1 和 6）。
 * 
 * 请你返回使 nums1 中所有数的和与 nums2 中所有数的和相等的最少操作次数。如果无法使两个数组的和相等，请返回 -1 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
 * 输出：3
 * 解释：你可以通过 3 次操作使 nums1 中所有数的和与 nums2 中所有数的和相等。以下数组下标都从 0 开始。
 * - 将 nums2[0] 变为 6 。 nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2] 。
 * - 将 nums1[5] 变为 1 。 nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2] 。
 * - 将 nums1[2] 变为 2 。 nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2] 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums1 = [1,1,1,1,1,1,1], nums2 = [6]
 * 输出：-1
 * 解释：没有办法减少 nums1 的和或者增加 nums2 的和使二者相等。
 * 
 * 
 * 示例 3：
 * 
 * 输入：nums1 = [6,6], nums2 = [1]
 * 输出：3
 * 解释：你可以通过 3 次操作使 nums1 中所有数的和与 nums2 中所有数的和相等。以下数组下标都从 0 开始。
 * - 将 nums1[0] 变为 2 。 nums1 = [2,6], nums2 = [1] 。
 * - 将 nums1[1] 变为 2 。 nums1 = [2,2], nums2 = [1] 。
 * - 将 nums2[0] 变为 4 。 nums1 = [2,2], nums2 = [4] 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums1.length, nums2.length <= 10^5
 * 1 <= nums1[i], nums2[i] <= 6
 * 
 * 
 */

// @lc code=start
class Solution {
    public int minOperations(int[] nums1, int[] nums2) {
        int[] vec1 = new int[7];
        int[] vec2 = new int[7];
        int n1 = nums1.length;
        int n2 = nums2.length;
        int sum1 = 0;
        int sum2 = 0;
        int maxN = Integer.max(n1, n2); 
        for(int i = 0; i < maxN; i++){
            if(i < n1)
            {
                vec1[nums1[i]]++;
                sum1 += nums1[i];
            }
            if(i < n2)
            {
                vec2[nums2[i]]++;
                sum2 += nums2[i];
            }
        }
        if(sum1 == sum2)
            return 0;
        else if(sum1 > sum2)
            return adjust(vec2, vec1, sum1 - sum2);
        else
            return adjust(vec1, vec2, sum2 - sum1);

    }

    int adjust(int small[], int big[], int gap){
        int res = 0;
        for(int i = 1; i < 6; i++){
            int mul = small[i] * (6 - i);
            if(mul >= gap){
                return res + dichotomy(1, small[i], 6 - i, gap);
            }else{
                res += small[i];
                gap -= mul;
            }
            mul = big[7 - i] *  (6 - i);
            if(mul >= gap){
                return res + dichotomy(1, big[7 - i], 6 - i, gap);
            }else{
                res += big[7-i];
                gap -= mul;
            }
        }
        return -1;
    }

    int dichotomy(int left, int right, int factor, int gap){
        while(left <= right - 1){
            int mid = (left + right)/2;
            int mul = mid * factor;
            int mul2 = mul + factor;
            if(mul > gap){
                right = mid;
            }else if(mul2 < gap){
                left = mid + 1;
            }else{
                if(mul < gap)
                    return mid + 1;
                else
                    return mid;
            }
        }
        return left;
    }
}
// @lc code=end

