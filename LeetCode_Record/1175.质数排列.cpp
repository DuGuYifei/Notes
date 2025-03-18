#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1175 lang=cpp
 *
 * [1175] 质数排列
 */

// @lc code=start
const int MOD = 1e9 + 7;
class Solution {
public:
    int numPrimeArrangements(int n) {
        if(n <= 2)
            return 1;
        int countP = countPrime(n);
        long res = 1;
        int i = 2;
        int countNP = (n - countP);
        int limit1 = countP < countNP? countP : countNP;
        int limit2 = countP > countNP? countP : countNP;
        for(; i <= limit1; i++)
        {
            res *= i;
            res %= MOD;
        }
        long res2 = res;
        for(;; i++)
        {
            if(i > limit2)
                break;
            res2 *= i;
            res2 %= MOD;
        }
        return res * res2 % MOD;
    }

    int countPrime(int n)
    {
        int res = 0;
        vector<bool> isP(n + 1, true);
        for(int i = 2; i <= n; i++)
        {
            if(isP[i])
            {
                res++;
                if(i*i <= n)
                    for(int j = i * i; j <= n; j+=i)
                    {
                        isP[j] = false;
                    }
            }
        }
        return res;
    }
};
// @lc code=end

