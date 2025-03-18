#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2029 lang=cpp
 *
 * [2029] 石子游戏 IX
 */

// @lc code=start
class Solution
{
public:
    bool stoneGameIX(vector<int> &stones)
    {
        int zero = 0, one = 0, two = 0, n = stones.size();
        if (n == 0)
            return false;
        for (int i = 0; i < n; i++)
        {
            if (int res = stones[i] % 3;!res)
                zero++;
            else if (res == 1)
                one++;
            else
                two++;
        }
        if (!(zero % 2))
        {
            return one && two;
        }
        return one-two > 2 || two - one >2 ;
    }
};
// @lc code=end
