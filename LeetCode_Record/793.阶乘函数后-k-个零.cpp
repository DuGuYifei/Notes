/*
 * @lc app=leetcode.cn id=793 lang=cpp
 *
 * [793] 阶乘函数后 K 个零
 */

// @lc code=start
class Solution
{
public:
    // 对 Σ(1->∞)[x/5^k] 求极限得到上下界为 (x/5, x/4)
    // 所以结果为k时候，x的取值范围是 (4k,5k)
    // 答案要么是 5 要么是 0， 所以如果能找打一个x就返回5，找不到就返回0；
    int preimageSizeFZF(int k) {
        long long r = 5LL*k;
        long long l = 4LL*k;
        while(r >= l)
        {
            long long mid = (l+r) >> 1;
            int tmp = countFive(mid);
            if(tmp > k)
                r = mid - 1;
            else if(tmp < k)
                l = mid + 1;
            else
                return 5;
        }
        return 0;
    }

    int countFive(long n)
    {
        int res = 0;
        while(n != 0)
        {
            res += n/5;
            n/=5;
        }
        return res;
    }
};
// @lc code=end
