/*
 * @lc app=leetcode.cn id=357 lang=cpp
 *
 * [357] 统计各位数字都不同的数字个数
 */

// @lc code=start
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        int ans = 10;
        int ans_t = 9;
        int num = 9;
        for(int i = n;i > 1;i-- )
        {
            ans_t *= num--;
            ans+=ans_t;
        }
        return ans;
    }
};
// @lc code=end

