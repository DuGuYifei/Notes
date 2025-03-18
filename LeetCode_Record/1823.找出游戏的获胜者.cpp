/*
 * @lc app=leetcode.cn id=1823 lang=cpp
 *
 * [1823] 找出游戏的获胜者
 */

// @lc code=start
//[这或许是你能找到的最详细约瑟夫环数学推导！](https://zhuanlan.zhihu.com/p/121159246)
class Solution
{
public:
    int findTheWinner(int n, int k)
    {
        if (n == 1)
            return 1;
        return (findTheWinner(n - 1, k) - 1 + k) % n + 1;
    }   
};
// @lc code=end
