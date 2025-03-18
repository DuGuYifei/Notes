import java.util.Arrays;

/*
 * @lc app=leetcode.cn id=1641 lang=java
 *
 * [1641] 统计字典序元音字符串的数目
 *
 * https://leetcode.cn/problems/count-sorted-vowel-strings/description/
 *
 * algorithms
 * Medium (77.94%)
 * Likes:    86
 * Dislikes: 0
 * Total Accepted:    17.1K
 * Total Submissions: 21.7K
 * Testcase Example:  '1'
 *
 * 给你一个整数 n，请返回长度为 n 、仅由元音 (a, e, i, o, u) 组成且按 字典序排列 的字符串数量。
 * 
 * 字符串 s 按 字典序排列 需要满足：对于所有有效的 i，s[i] 在字母表中的位置总是与 s[i+1] 相同或在 s[i+1] 之前。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 1
 * 输出：5
 * 解释：仅由元音组成的 5 个字典序字符串为 ["a","e","i","o","u"]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 2
 * 输出：15
 * 解释：仅由元音组成的 15 个字典序字符串为
 * ["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"]
 * 注意，"ea" 不是符合题意的字符串，因为 'e' 在字母表中的位置比 'a' 靠后
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 33
 * 输出：66045
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1  
 * 
 * 
 */

// @lc code=start
class Solution {
    public int countVowelStrings(int n) {
        // int[][] dp = new int[n][5];
        // dp[0] = new int[]{1, 1, 1, 1, 1};
        // for(int i = 1; i < n; i++){
        //     dp[i][0] = dp[i - 1][0];
        //     for(int j = 1; j < 5; j++){
        //         dp[i][j] = dp[i-1][j] + dp[i][j - 1];
        //         System.out.println(dp[i][j]);
        //     }
        // }
        // return Arrays.stream(dp[n - 1]).sum();
        int[] dp = new int[5];
        Arrays.fill(dp, 1);
        for(int i = 1; i < n; i++){
            for(int j = 1; j < 5; j++){
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        return Arrays.stream(dp).sum();
    }
}
// @lc code=end

