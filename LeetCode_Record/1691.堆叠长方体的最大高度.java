import java.util.Arrays;

/*
 * @lc app=leetcode.cn id=1691 lang=java
 *
 * [1691] 堆叠长方体的最大高度
 *
 * https://leetcode-cn.com/problems/maximum-height-by-stacking-cuboids/description/
 *
 * algorithms
 * Hard (49.41%)
 * Likes:    49
 * Dislikes: 0
 * Total Accepted:    4K
 * Total Submissions: 7.5K
 * Testcase Example:  '[[50,45,20],[95,37,53],[45,23,12]]'
 *
 * 给你 n 个长方体 cuboids ，其中第 i 个长方体的长宽高表示为 cuboids[i] = [widthi, lengthi,
 * heighti]（下标从 0 开始）。请你从 cuboids 选出一个 子集 ，并将它们堆叠起来。
 * 
 * 如果 widthi j 且 lengthi j 且 heighti j ，你就可以将长方体 i 堆叠在长方体 j
 * 上。你可以通过旋转把长方体的长宽高重新排列，以将它放在另一个长方体上。
 * 
 * 返回 堆叠长方体 cuboids 可以得到的 最大高度 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：cuboids = [[50,45,20],[95,37,53],[45,23,12]]
 * 输出：190
 * 解释：
 * 第 1 个长方体放在底部，53x37 的一面朝下，高度为 95 。
 * 第 0 个长方体放在中间，45x20 的一面朝下，高度为 50 。
 * 第 2 个长方体放在上面，23x12 的一面朝下，高度为 45 。
 * 总高度是 95 + 50 + 45 = 190 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：cuboids = [[38,25,45],[76,35,3]]
 * 输出：76
 * 解释：
 * 无法将任何长方体放在另一个上面。
 * 选择第 1 个长方体然后旋转它，使 35x3 的一面朝下，其高度为 76 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
 * 输出：102
 * 解释：
 * 重新排列长方体后，可以看到所有长方体的尺寸都相同。
 * 你可以把 11x7 的一面朝下，这样它们的高度就是 17 。
 * 堆叠长方体的最大高度为 6 * 17 = 102 。
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * n == cuboids.length
 * 1 
 * 1 i, lengthi, heighti 
 * 
 * 
 */

// @lc code=start
class Solution {
    public int maxHeight(int[][] cuboids) {
        for(int[] i : cuboids){
            Arrays.sort(i);
        }
        Arrays.sort(cuboids, (a,b)->{int s = (a[2] - b[2]); return s == 0? (a[1] - b[1] == 0? a[0] - b [0] : a[1] - b[1]): s;});
        int n = cuboids.length;
        int[] dp = new int[n];
        int ans = cuboids[0][2];
        dp[0] = cuboids[0][2];
        for(int i = 1; i < n; i++){
            dp[i] = cuboids[i][2];
            for(int j = 0; j < i; j++){
                if(cuboids[i][0] >= cuboids[j][0] && cuboids[i][1] >= cuboids[j][1]){
                    dp[i] = Math.max(dp[i], dp[j] + cuboids[i][2]);
                }
            }
            ans = Math.max(ans, dp[i]);
        }
        return ans;
    }
}
// @lc code=end

