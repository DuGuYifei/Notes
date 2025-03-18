#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1017 lang=cpp
 *
 * [1017] 负二进制转换
 *
 * https://leetcode.cn/problems/convert-to-base-2/description/
 *
 * algorithms
 * Medium (57.11%)
 * Likes:    68
 * Dislikes: 0
 * Total Accepted:    6.2K
 * Total Submissions: 10.6K
 * Testcase Example:  '2'
 *
 * 给你一个整数 n ，以二进制字符串的形式返回该整数的 负二进制（base -2）表示。
 * 
 * 注意，除非字符串就是 "0"，否则返回的字符串中不能含有前导零。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 2
 * 输出："110"
 * 解释：(-2)^2 + (-2)^1 = 2
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 3
 * 输出："111"
 * 解释：(-2)^2 + (-2)^1 + (-2)^0 = 3
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 4
 * 输出："100"
 * 解释：(-2)^2 = 4
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= n <= 10^9
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string baseNeg2(int n) {
	    if (n == 0) {
	    	return "0";
	    }
	    int res = 0b1010101010101010101010101010101 ^ (0b1010101010101010101010101010101 - n);
	    string ans;
	    while (res > 0) {
	    	ans.append(1, (res&1)+'0');
	    	res >>= 1;
	    }
	    reverse(ans.begin(), ans.end());
        return ans;
    }
};
// @lc code=end

