/*
 * @lc app=leetcode.cn id=172 lang=cpp
 *
 * [172] 阶乘后的零
 */

// @lc code=start
class Solution {
public:
    int trailingZeroes(int n) {
        // 牢记：计算机除法必须挨个除再加，不能求和再除，因为它会向下取整
        int ans = 0;
        while(n != 0)
        {
            ans += n/5;
            n = n/5;
        }
        return ans;
    }
};
// @lc code=end

