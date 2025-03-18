#include <algorithm>
/*
 * @lc app=leetcode.cn id=479 lang=cpp
 *
 * [479] 最大回文数乘积
 */

// @lc code=start
class Solution
{
public:
    int largestPalindrome(int n)
    {
        if(n == 1) return 9;
        int limit = pow(10, n) - 1;
        for (int left = limit;; left--)
        {
            long p = left;
            for (int i = left; i > 0; i /= 10)
            {
                p = p * 10 + i % 10; // 反转这个数获得回文数
            }
            for (long i = limit; i * i >= p; i--)
            {
                if (p % i == 0)
                    return p % 1337;
            }
        }
    }
};
// @lc code=end
