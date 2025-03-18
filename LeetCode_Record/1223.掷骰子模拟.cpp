#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1223 lang=cpp
 *
 * [1223] 掷骰子模拟
 *
 * https://leetcode-cn.com/problems/dice-roll-simulation/description/
 *
 * algorithms
 * Hard (47.84%)
 * Likes:    148
 * Dislikes: 0
 * Total Accepted:    8.5K
 * Total Submissions: 14.6K
 * Testcase Example:  '2\n[1,1,2,2,2,3]'
 *
 * 有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。
 * 
 * 不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]（i 从 1 开始编号）。
 * 
 * 现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。
 * 
 * 假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：n = 2, rollMax = [1,1,2,2,2,3]
 * 输出：34
 * 解释：我们掷 2 次骰子，如果没有约束的话，共有 6 * 6 = 36 种可能的组合。但是根据 rollMax 数组，数字 1 和 2
 * 最多连续出现一次，所以不会出现序列 (1,1) 和 (2,2)。因此，最终答案是 36-2 = 34。
 * 
 * 
 * 示例 2：
 * 
 * 输入：n = 2, rollMax = [1,1,1,1,1,1]
 * 输出：30
 * 
 * 
 * 示例 3：
 * 
 * 输入：n = 3, rollMax = [1,1,1,2,2,3]
 * 输出：181
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 5000
 * rollMax.length == 6
 * 1 <= rollMax[i] <= 15
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    static constexpr int mod = 1E9 + 7;
    int dieSimulator(int n, vector<int>& rollMax) {
        vector<vector<vector<int>>> d(n + 1, vector(6, vector<int>(16)));
        for(int j = 0; j < 6; j++){
            d[1][j][1] = 1;
        }
        for(int i = 2; i <= n; i++){
            for(int j = 0; j < 6; j++){
                for(int k = 1; k <= rollMax[j]; k++){
                    for(int p = 0; p < 6; p++){
                        if(p != j)
                            d[i][p][1] = (d[i][p][1] + d[i - 1][j][k]) % mod;
                        else if (k + 1 <= rollMax[j])
                            d[i][p][k + 1] = (d[i][p][k + 1] + d[i - 1][j][k]) % mod;
                    }
                }
            }
        }
        int res = 0;
        for(int j = 0; j < 6; j++)
            for(int k = 1; k <= rollMax[j]; k++)
                res = (res + d[n][j][k]) % mod;
        return res;
    }
};
// @lc code=end

