#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=878 lang=cpp
 *
 * [878] 第 N 个神奇数字
 *
 * https://leetcode-cn.com/problems/nth-magical-number/description/
 *
 * algorithms
 * Hard (29.07%)
 * Likes:    159
 * Dislikes: 0
 * Total Accepted:    13.2K
 * Total Submissions: 35.9K
 * Testcase Example:  '1\n2\n3'
 *
 * 一个正整数如果能被 a 或 b 整除，那么它是神奇的。
 * 
 * 给定三个整数 n , a , b ，返回第 n 个神奇的数字。因为答案可能很大，所以返回答案 对 10^9 + 7 取模 后的值。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 1, a = 2, b = 3
 * 输出：2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 4, a = 2, b = 3
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 10^9
 * 2 <= a, b <= 4 * 10^4
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        int minab = min(a,b);
        int maxab = max(a,b);
        long long l = a * b / gcd(a,b);
        int groupNum = l / a + l / b - 1;
        int group = n / groupNum;
        int remain = n % groupNum;
        long long adda = l * group;
        long long addb = adda;
        int t = maxab / minab;
        
        for(int i = 0; i < remain; i++)
        {
            if(adda + minab < addb + maxab)
                adda += minab;
            else
                addb += maxab;
        }
        return max(adda, addb) % ((int)1e9+7);
    }
    int gcd(int a, int b){
        if (b == 0) return a;
        return gcd(b,a%b);
    }
};
// @lc code=end

