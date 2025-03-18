#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=1015 lang=cpp
 *
 * [1015] 可被 K 整除的最小整数
 *
 * https://leetcode.cn/problems/smallest-integer-divisible-by-k/description/
 *
 * algorithms
 * Medium (37.11%)
 * Likes:    65
 * Dislikes: 0
 * Total Accepted:    8.1K
 * Total Submissions: 20.8K
 * Testcase Example:  '1'
 *
 * 给定正整数 k ，你需要找出可以被 k 整除的、仅包含数字 1 的最 小 正整数 n 的长度。
 * 
 * 返回 n 的长度。如果不存在这样的 n ，就返回-1。
 * 
 * 注意： n 不符合 64 位带符号整数。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：k = 1
 * 输出：1
 * 解释：最小的答案是 n = 1，其长度为 1。
 * 
 * 示例 2：
 * 
 * 
 * 输入：k = 2
 * 输出：-1
 * 解释：不存在可被 2 整除的正整数 n 。
 * 
 * 示例 3：
 * 
 * 
 * 输入：k = 3
 * 输出：3
 * 解释：最小的答案是 n = 111，其长度为 3。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= k <= 10^5
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        unordered_set<int> resids;
        int len = 1;
        int resid = 1 % k;
        while(resid){
            if(resids.find(resid) != resids.end())
                return -1;
            resids.emplace(resid);
            resid = (resid * 10 + 1) % k;
            len++;
        }
        return len;
    }
};
// @lc code=end

