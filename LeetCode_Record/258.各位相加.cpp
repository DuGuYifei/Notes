/*
 * @lc app=leetcode.cn id=258 lang=cpp
 *
 * [258] 各位相加
 */

// @lc code=start
class Solution {
public:
    int addDigits(int num) {
        // while(num>9)
        // {
        //     int ans = 0;
        //     while(num!=0)
        //     {
        //         ans += num%10;
        //         num /=10;
        //     }
        //     num = ans;
        // }
        // return num;
        if(num ==0) return 0;
        int ans = num%9;
        if(ans == 0) return 9;
        return ans;
    }
};
// @lc code=end

