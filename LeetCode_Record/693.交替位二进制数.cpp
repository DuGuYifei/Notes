/*
 * @lc app=leetcode.cn id=693 lang=cpp
 *
 * [693] 交替位二进制数
 */

// @lc code=start
class Solution {
public:
    bool hasAlternatingBits(int n) {
        long temp = n ^ (n>>1);
        return ((temp +  1) & temp)  == 0;
    }
};
// @lc code=end

