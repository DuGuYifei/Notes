/*
 * @lc app=leetcode.cn id=868 lang=cpp
 *
 * [868] 二进制间距
 */

// @lc code=start
class Solution
{
public:
    int binaryGap(int n)
    {
        // int maxdis = 0;
        // int dis = 0;
        // while ((n & (-n)) != 1)
        //     n >>= 1;
        // n>>=1;
        // while (n > 0)
        // {
        //     if ((n & (-n)) != 1)
        //     {
        //         dis++;
        //     }
        //     else
        //     {
        //         dis++;
        //         maxdis = max(maxdis, dis);
        //         dis = 0;
        //     }
        //     n = n >> 1;
        // }
        // return maxdis;

        int last = -1, ans = 0;
        for(int i = 0; n; i++)
        {
            if(n&1)
            {
                if(last != -1)
                {
                    ans = max(ans, i - last);
                }
                last = i;
            }
            n>>=1;
        }
        return ans;
    }
};
// @lc code=end
