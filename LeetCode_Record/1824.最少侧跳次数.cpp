#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=1824 lang=cpp
 *
 * [1824] 最少侧跳次数
 *
 * https://leetcode-cn.com/problems/minimum-sideway-jumps/description/
 *
 * algorithms
 * Medium (64.61%)
 * Likes:    48
 * Dislikes: 0
 * Total Accepted:    11K
 * Total Submissions: 17K
 * Testcase Example:  '[0,1,2,3,0]'
 *
 * 给你一个长度为 n 的 3 跑道道路 ，它总共包含 n + 1 个 点 ，编号为 0 到 n 。一只青蛙从 0 号点第二条跑道 出发 ，它想要跳到点 n
 * 处。然而道路上可能有一些障碍。
 *
 * 给你一个长度为 n + 1 的数组 obstacles ，其中 obstacles[i] （取值范围从 0 到 3）表示在点 i 处的
 * obstacles[i] 跑道上有一个障碍。如果 obstacles[i] == 0 ，那么点 i 处没有障碍。任何一个点的三条跑道中 最多有一个
 * 障碍。
 *
 *
 * 比方说，如果 obstacles[2] == 1 ，那么说明在点 2 处跑道 1 有障碍。
 *
 *
 * 这只青蛙从点 i 跳到点 i + 1 且跑道不变的前提是点 i + 1 的同一跑道上没有障碍。为了躲避障碍，这只青蛙也可以在 同一个 点处 侧跳 到
 * 另外一条 跑道（这两条跑道可以不相邻），但前提是跳过去的跑道该点处没有障碍。
 *
 *
 * 比方说，这只青蛙可以从点 3 处的跑道 3 跳到点 3 处的跑道 1 。
 *
 *
 * 这只青蛙从点 0 处跑道 2 出发，并想到达点 n 处的 任一跑道 ，请你返回 最少侧跳次数 。
 *
 * 注意：点 0 处和点 n 处的任一跑道都不会有障碍。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：obstacles = [0,1,2,3,0]
 * 输出：2
 * 解释：最优方案如上图箭头所示。总共有 2 次侧跳（红色箭头）。
 * 注意，这只青蛙只有当侧跳时才可以跳过障碍（如上图点 2 处所示）。
 *
 *
 * 示例 2：
 *
 *
 * 输入：obstacles = [0,1,1,3,3,0]
 * 输出：0
 * 解释：跑道 2 没有任何障碍，所以不需要任何侧跳。
 *
 *
 * 示例 3：
 *
 *
 * 输入：obstacles = [0,2,1,0,3,0]
 * 输出：2
 * 解释：最优方案如上图所示。总共有 2 次侧跳。
 *
 *
 *
 *
 * 提示：
 *
 *
 * obstacles.length == n + 1
 * 1
 * 0
 * obstacles[0] == obstacles[n] == 0
 *
 *
 */

// @lc code=start
class Solution {
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size() - 1;
        vector<vector<int>> dp(n + 1, vector<int>(3));
        dp[0] = {1, 0, 1};
        for(int pos = 0; pos < n; pos++){
            for(int track = 0; track < 3; track++){
                if(obstacles[pos + 1] != track + 1){
                    if(obstacles[pos] != track + 1)
                        dp[pos + 1][track] = dp[pos][track];
                    else{
                        dp[pos + 1][track] = min(
                            dp[pos][(track + 1) % 3] + 1 + (obstacles[pos + 1] == (track + 1) % 3 + 1),
                            dp[pos][(track + 2) % 3] + 1 + (obstacles[pos + 1] == (track + 2) % 3 + 1)
                        );
                    }
                }
            }
        }
        return *min_element(dp[n].begin(), dp[n].end());
    }
};
// class Solution
// {
// public:
//     int minSideJumps(vector<int> &obstacles)
//     {
//         int n = obstacles.size() - 1;
//         vector<vector<int>> visited(n + 1, vector<int>(3, -1));
//         queue<tuple<int, int, int>> qu;
//         qu.emplace(0, 1, 0);
//         while (!qu.empty())
//         {
//             int cnt = qu.size();
//             while(cnt > 0)
//             {
//                 cnt--;
//                 auto [pos, track, jump] = qu.front();
//                 qu.pop();
//                 if (visited[pos][track] != -1)
//                     continue;
//                 visited[pos][track] = jump;
//                 if (obstacles[pos + 1] != track + 1)
//                 {
//                     if (pos + 1 == n)
//                         return jump;
//                     qu.emplace(pos + 1, track, jump);
//                 }
//                 if (obstacles[pos] != (track + 1) % 3 + 1)
//                     qu.emplace(pos, (track + 1) % 3, jump + 1);
//                 if (obstacles[pos] != (track + 2) % 3 + 1)
//                     qu.emplace(pos, (track + 2) % 3, jump + 1);
//             }
//         }
//         return 0;
//     }
// };
// @lc code=end
