#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1663 lang=cpp
 *
 * [1663] 具有给定数值的最小字符串
 *
 * https://leetcode-cn.com/problems/smallest-string-with-a-given-numeric-value/description/
 *
 * algorithms
 * Medium (57.47%)
 * Likes:    76
 * Dislikes: 0
 * Total Accepted:    20.4K
 * Total Submissions: 32K
 * Testcase Example:  '3\n27'
 *
 * 小写字符 的 数值 是它在字母表中的位置（从 1 开始），因此 a 的数值为 1 ，b 的数值为 2 ，c 的数值为 3 ，以此类推。
 * 
 * 字符串由若干小写字符组成，字符串的数值 为各字符的数值之和。例如，字符串 "abe" 的数值等于 1 + 2 + 5 = 8 。
 * 
 * 给你两个整数 n 和 k 。返回 长度 等于 n 且 数值 等于 k 的 字典序最小 的字符串。
 * 
 * 注意，如果字符串 x 在字典排序中位于 y 之前，就认为 x 字典序比 y 小，有以下两种情况：
 * 
 * 
 * x 是 y 的一个前缀；
 * 如果 i 是 x[i] != y[i] 的第一个位置，且 x[i] 在字母表中的位置比 y[i] 靠前。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 3, k = 27
 * 输出："aay"
 * 解释：字符串的数值为 1 + 1 + 25 = 27，它是数值满足要求且长度等于 3 字典序最小的字符串。
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 5, k = 73
 * 输出："aaszz"
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * n 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string getSmallestString(int n, int k) {
        int left = 0, right = n;
        while(left < right){
            int mid = (left + right + 1) >> 1;
            if(n - mid + mid * 26 > k){
                right = mid - 1;
            }else{
                left = mid;
            }
        }
        string ans = "";
        int amend = k - n + left - left * 26;
        int amendExist = amend > 0;
        ans.append(n - left - amendExist, 'a');
        ans.append(amendExist, amend + 'a');
        ans.append(left, 'z');
        return ans;
    }
};
// @lc code=end

