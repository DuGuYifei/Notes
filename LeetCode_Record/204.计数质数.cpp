/*
 * @lc app=leetcode.cn id=204 lang=cpp
 *
 * [204] 计数质数
 */

// @lc code=start
class Solution
{
public:
    // bool isPrime(int x)
    // {
    //     for (int i = 2; i * i <= x; i++)
    //     {
    //         if (!(x % i))
    //         {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
    int countPrimes(int n)
    {
        //     int ans = 0;
        //     for (int i = 2; i < n; i++)
        //     {
        //         ans+=isPrime(i);
        //     }
        //     return ans;

        // 埃氏筛
        vector<int> isPrime(n, 1);
        int ans = 0;
        for (int i = 2; i < n; i++)
        {
            if (isPrime[i])
            {
                ans++;
                if((long)i * i < n)
                for(int j = i * i; j<n; j += i)
                {
                    isPrime[j]= 0;
                }
            }
        }
        return ans;
    }
};
// @lc code=end
