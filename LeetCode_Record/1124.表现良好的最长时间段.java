import java.util.Stack;

/*
 * @lc app=leetcode.cn id=1124 lang=java
 *
 * [1124] 表现良好的最长时间段
 *
 * https://leetcode-cn.com/problems/longest-well-performing-interval/description/
 *
 * algorithms
 * Medium (32.92%)
 * Likes:    441
 * Dislikes: 0
 * Total Accepted:    38.5K
 * Total Submissions: 99.2K
 * Testcase Example:  '[9,9,6,0,6,6,9]'
 *
 * 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。
 * 
 * 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。
 * 
 * 所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。
 * 
 * 请你返回「表现良好时间段」的最大长度。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：hours = [9,9,6,0,6,6,9]
 * 输出：3
 * 解释：最长的表现良好时间段是 [9,9,6]。
 * 
 * 示例 2：
 * 
 * 
 * 输入：hours = [6,6,6]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= hours.length <= 10^4
 * 0 <= hours[i] <= 16
 * 
 * 
 */

// @lc code=start
class Solution {
    public int longestWPI(int[] hours) {
        int n = hours.length;
        int[] prefix = new int[n + 1];
        Stack<Integer>  mono = new Stack<>();
        mono.push(0);
        for(int i = 1; i <= n; i++){
            if(hours[i - 1] > 8)
                prefix[i] = prefix[i - 1] + 1;
            else
                prefix[i] = prefix[i - 1] - 1;
            if(prefix[i] < prefix[mono.peek()])
                mono.push(i);
        }

        int ans = 0;
        for(int i = n; i > 0; i--){
            while(prefix[i] > prefix[mono.peek()]){
                ans = Integer.max(ans, i - mono.peek());
                mono.pop();
                if(mono.empty())
                    return ans;
            }
        }
        return ans;
    }
}
// @lc code=end

