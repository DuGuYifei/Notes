/*
 * @lc app=leetcode.cn id=762 lang=cpp
 *
 * [762] 二进制表示中质数个计算置位
 */

// @lc code=start
class Solution {
public:

    int countPrimeSetBits(int left, int right) {
        int ans = 0;
        //right <= 10^6 < 2^20
        for(int i = left;i<=right;i++)
        {
            int count_1 = 0;
            int t = i;
            while(t)
            {
                t &= t-1;
                count_1++;
            }
            //将1左移count_1位，对准
            if((1<<count_1)& 0b10100010100010101100)
            {
                ans++;
            }
        }
        return ans;
    }
};
// @lc code=end

