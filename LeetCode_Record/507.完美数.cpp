/*
 * @lc app=leetcode.cn id=507 lang=cpp
 *
 * [507] 完美数
 */

// @lc code=start
class Solution
{
public:
    bool checkPerfectNumber(int num)
    {
        if (num == 1)
            return false;
        int sum = 1;
        int i = 2;
        while (i * i <= num)
        {
            if (num % i == 0)
            {
                sum += i;
                sum += num / i;
            }
            i++;
        }
        if (sum == num)
        {
            return true;
        }
        else
            return false;
    }
};
// @lc code=end
