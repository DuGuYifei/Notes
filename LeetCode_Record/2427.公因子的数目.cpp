/*
 * @lc app=leetcode.cn id=2427 lang=cpp
 *
 * [2427] 公因子的数目
 *
 * https://leetcode.cn/problems/number-of-common-factors/description/
 *
 * algorithms
 * Easy (81.49%)
 * Likes:    13
 * Dislikes: 0
 * Total Accepted:    12.1K
 * Total Submissions: 14.9K
 * Testcase Example:  '12\n6'
 *
 * 给你两个正整数 a 和 b ，返回 a 和 b 的 公 因子的数目。
 * 
 * 如果 x 可以同时整除 a 和 b ，则认为 x 是 a 和 b 的一个 公因子 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：a = 12, b = 6
 * 输出：4
 * 解释：12 和 6 的公因子是 1、2、3、6 。
 * 
 * 
 * 示例 2：
 * 
 * 输入：a = 25, b = 30
 * 输出：2
 * 解释：25 和 30 的公因子是 1、5 。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= a, b <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int commonFactors(int a, int b) {
        int c = gcd(a, b);
        int ans = 0;
        for(int i = 1; i * i <= c; i++){
            if(c % i == 0){
                ans++;
                if(i * i != c) ans++;
            }
        }
        return ans;
    }

    int gcd(int a, int b){
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};
// @lc code=end

