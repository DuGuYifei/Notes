#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1994 lang=cpp
 *
 * [1994] 好子集的数目
 */

// @lc code=start
class Solution
{
    int mod = 1000000007;
    // int premier[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    //特殊：6，10，14，15，21，22，26，30
    int bad[11] = {4, 8, 9, 12, 16, 18, 20, 24, 25, 27, 28};

public:
    int numberOfGoodSubsets(vector<int> &nums)
    {
        int freq[31] = {0};
        // 每个数有多少个个数
        for (int &num : nums)
        {
            freq[num]++;
        }

        // 状态压缩存储初始化长度和值为0,因为有十个质数所以1<<10就是2^10次方种可能(结束位索引为2^10-1)
        // 此向量表示每一种可能性的集合个数
        vector<int> state(1 << 10);

        // 计算state[0]，即只有1的时候，2^freq[0]
        state[0] = 1;
        for (int i = 0; i < freq[1]; i++)
        {
            state[0] = state[0] * 2 % mod; // 防止超过int范围
        }

        for (int i = 2; i < 31; i++)
        {
            // 向量中没有这个数 或 是个坏数，不用考虑
            if (freq[i] == 0 || *find(bad, bad + 10, i) == i)
            {
                continue;
            }
            // 表示i子质数因子的state，默认0，因为如果不是特殊值，用state异或0还是会是自己
            int subset = 0;
            switch (i)
            {
            case 6:
                subset = 0b11;
                break;
            case 10:
                subset = 0b101;
                break;
            case 14:
                subset = 0b1001;
                break;
            case 15:
                subset = 0b110;
                break;
            case 21:
                subset = 0b1010;
                break;
            case 22:
                subset = 0b10001;
                break;
            case 26:
                subset = 0b100001;
                break;
            case 30:
                subset = 0b111;
                break;

            case 2:
                subset = 0b1;
                break;
            case 3:
                subset = 0b10;
                break;
            case 5:
                subset = 0b100;
                break;
            case 7:
                subset = 0b1000;
                break;
            case 11:
                subset = 0b10000;
                break;
            case 13:
                subset = 0b100000;
                break;
            case 17:
                subset = 0b1000000;
                break;
            case 19:
                subset = 0b10000000;
                break;
            case 23:
                subset = 0b100000000;
                break;
            case 29:
                subset = 0b1000000000;
                break;
            }

            // 动态规划，因为i是从前往后遍历的，所以遇到写在最上面的特殊数，
            //一定已经获得过不包含特殊数分解因子的剩余因子组成的结果了
            // 不包含空集，所以j>0
            for (int j = (1 << 10) - 1; j > 0; j--)
            {
                // 如果是特殊值，则需要跳过包含特殊值质因子的state
                if ((j & subset) == subset) // 说明state j不包含subset
                {
                    // state j 的结果其实等于包含特殊值质因子的结果再乘以特殊值的个数（如果是特殊值的话）
                    // j^subset 相同时会取到 state[0] 所以不经意间就把1带进去算了
                    state[j] = (state[j] + static_cast<long long>(state[j ^ subset]) * freq[i]) % mod;
                }
            }
        }

        int ans = 0;
        for (int i = 1; i < (1 << 10); i++)
        {
            ans = (ans + state[i]) % mod;
        }
        return ans;
    }
};
// @lc code=end
