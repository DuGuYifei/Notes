#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1703 lang=cpp
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
public:
    int minMoves(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> one_id;
        for(int i = 0; i < n; i++){
            if(nums[i]){
                one_id.push_back(i);
            }
        }
        int ans = 0;
        for(int i = 1; i < k; i++){
            // * min(i, k-i) 相当于把前面先移动到下一位前的数一起往中键移
            ans += (one_id[i] - one_id[i - 1] - 1) * min(i, k - i);
        }
        int temp = ans;
        int m = one_id.size();
        int mid = k/2;
        for(int i = k; i < m; i++){
            // + 当前右端点-中位数  - （上区间中位数 - 左端点）
            // 就是把最左边移动的位数减掉换成右边的
            temp += one_id[i] - one_id[i -mid] - one_id[i - k + mid] + one_id[i - k];
            ans = min(ans, temp);
        }
        return ans;
    }
};
// @lc code=end

