import java.util.ArrayList;

/*
 * @lc app=leetcode.cn id=1703 lang=java
 *
 * [1703] 得到连续 K 个 1 的最少相邻交换次数
 *
 * https://leetcode-cn.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/description/
 *
 * algorithms
 * Hard (38.40%)
 * Likes:    66
 * Dislikes: 0
 * Total Accepted:    3.1K
 * Total Submissions: 7.5K
 * Testcase Example:  '[1,0,0,1,0,1]\n2'
 *
 * 给你一个整数数组 nums 和一个整数 k 。 nums 仅包含 0 和 1 。每一次移动，你可以选择 相邻 两个数字并将它们交换。
 * 
 * 请你返回使 nums 中包含 k 个 连续 1 的 最少 交换次数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：nums = [1,0,0,1,0,1], k = 2
 * 输出：1
 * 解释：在第一次操作时，nums 可以变成 [1,0,0,0,1,1] 得到连续两个 1 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：nums = [1,0,0,0,0,0,1,1], k = 3
 * 输出：5
 * 解释：通过 5 次操作，最左边的 1 可以移到右边直到 nums 变为 [0,0,0,0,0,1,1,1] 。
 * 
 * 
 * 示例 3：
 * 
 * 输入：nums = [1,1,0,1], k = 2
 * 输出：0
 * 解释：nums 已经有连续 2 个 1 了。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums[i] 要么是 0 ，要么是 1 。
 * 1 <= k <= sum(nums)
 * 
 * 
 */

// @lc code=start
class Solution {
    public int minMoves(int[] nums, int k) {
        int n = nums.length;
        ArrayList<Integer> index = new ArrayList<>();
        for(int i = 0; i < n; i++){
            if(nums[i] == 1){
                index.add(i);
            }
        }
        int ans = 0;
        for(int i = 1; i < k; i++){
            ans += (index.get(i) - index.get(i-1) -1) * Math.min(i, k-i);
        }
        int temp = ans;
        int m = index.size();
        int mid = k/2;
        for(int i = k; i < m; i++){
            temp += index.get(i) - index.get(i-mid) - index.get(i - k + mid) + index.get(i - k);
            ans = Math.min(temp, ans);
        }
        return ans;
    }
}
// @lc code=end

