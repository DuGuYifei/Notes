#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1140 lang=cpp
 *
 * [1140] 石子游戏 II
 *
 * https://leetcode.cn/problems/stone-game-ii/description/
 *
 * algorithms
 * Medium (66.28%)
 * Likes:    271
 * Dislikes: 0
 * Total Accepted:    24.1K
 * Total Submissions: 34.2K
 * Testcase Example:  '[2,7,9,4,4]'
 *
 * 爱丽丝和鲍勃继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。
 * 
 * 爱丽丝和鲍勃轮流进行，爱丽丝先开始。最初，M = 1。
 * 
 * 在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。
 * 
 * 游戏一直持续到所有石子都被拿走。
 * 
 * 假设爱丽丝和鲍勃都发挥出最佳水平，返回爱丽丝可以得到的最大数量的石头。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：piles = [2,7,9,4,4]
 * 输出：10
 * 解释：如果一开始Alice取了一堆，Bob取了两堆，然后Alice再取两堆。爱丽丝可以得到2 + 4 + 4 =
 * 10堆。如果Alice一开始拿走了两堆，那么Bob可以拿走剩下的三堆。在这种情况下，Alice得到2 + 7 = 9堆。返回10，因为它更大。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入：piles = [1,2,3,4,5,100]
 * 输出：104
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= piles.length <= 100
 * 1 <= piles[i] <= 10^4
 * 
 * 
 */

// @lc code=start
/*
思考：
倒推，因为我们只能比较容易想出最后一个人最优怎么取

比如：
1. 我能全拿走就全拿走
2. 我不能全拿走，就想尽可能让对方少拿，
   什么是少拿，就是下个人把能取的都取走后剩下尽量多给我
   遍历我取了 1~2M 的所有可能
*/
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        int sum = 0; // 后缀和
        
        // dp[已取走堆数][M] = 爱丽丝
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        
        //i 已经取走的堆数，i = n是全取完的情况下，这时不用算就知道是0
        for(int i = n - 1; i >= 0; i--)
        {
            sum += piles[i];
            for(int M = 1; M <= n; M++)
            {
                int max_m = M * 2;
                if(max_m + i >= n)
                {
                    dp[i][M] = sum;
                }
                else
                {
                    // X 是当前为M情况下取走多少，即max(X,M)为下一个人的M
                    for(int X = 1; X <= max_m; X++)
                    {
                        dp[i][M] = max(dp[i][M], sum - dp[i + X][max(X, M)]);
                    }
                }
            }
        }
        return dp[0][1];
    }
};
// @lc code=end

