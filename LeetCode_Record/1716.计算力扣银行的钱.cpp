/*
 * @lc app=leetcode.cn id=1716 lang=cpp
 *
 * [1716] 计算力扣银行的钱
 */

// @lc code=start
class Solution {
public:
    int totalMoney(int n) {
        int week = n/7;
        int day = n%7;
        return (7*(week-1)+56)*week /2 + (day+1) * day / 2 + week *  day;
    }
};
// @lc code=end

