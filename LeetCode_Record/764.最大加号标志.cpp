#include <vector>
#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=764 lang=cpp
 *
 * [764] 最大加号标志
 *
 * https://leetcode-cn.com/problems/largest-plus-sign/description/
 *
 * algorithms
 * Medium (50.01%)
 * Likes:    117
 * Dislikes: 0
 * Total Accepted:    7.2K
 * Total Submissions: 14K
 * Testcase Example:  '5\n[[4,2]]'
 *
 * 在一个 n x n 的矩阵 grid 中，除了在数组 mines 中给出的元素为 0，其他每个元素都为 1。mines[i] = [xi, yi]表示
 * grid[xi][yi] == 0
 *
 * 返回  grid 中包含 1 的最大的 轴对齐 加号标志的阶数 。如果未找到加号标志，则返回 0 。
 *
 * 一个 k 阶由 1 组成的 “轴对称”加号标志 具有中心网格 grid[r][c] == 1 ，以及4个从中心向上、向下、向左、向右延伸，长度为
 * k-1，由 1 组成的臂。注意，只有加号标志的所有网格要求为 1 ，别的网格可能为 0 也可能为 1 。
 *
 *
 *
 * 示例 1：
 *
 *
 *
 *
 * 输入: n = 5, mines = [[4, 2]]
 * 输出: 2
 * 解释: 在上面的网格中，最大加号标志的阶只能是2。一个标志已在图中标出。
 *
 *
 * 示例 2：
 *
 *
 *
 *
 * 输入: n = 1, mines = [[0, 0]]
 * 输出: 0
 * 解释: 没有加号标志，返回 0 。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 500
 * 1 <= mines.length <= 5000
 * 0 <= xi, yi < n
 * 每一对 (xi, yi) 都 不重复​​​​​​​
 *
 *
 */

// @lc code=start
class Solution
{
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>> &mines)
    {
        unordered_set<int> bans;
        if(mines.size() == n * n)
            return 0;
        
        for (auto &i : mines)
            bans.emplace(i[0] * n + i[1]);
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(4)));

        int mid = (n - 1) / 2;
        int ans = 1;
        // mid + 1 - ans + 1 - 1
        for (int i = 0; i <= mid - ans; i++)
        {
            for (int j = 0; j <= mid - ans; j++)
            {
                int x = mid - i;
                int y = mid - j;
                int res = n;
                int maxres = min(x + 1, y + 1);

                if (!bans.count(x * n + y))
                {
                    dp[x][y] = {1, 1, 1, 1};
                    // x-- 方向
                    if (dp[x + 1][y][0])
                        dp[x][y][0] = dp[x + 1][y][0] - 1;
                    else
                        for (int dis = 1; dis <= x; dis++)
                        {
                            if (bans.count((x - dis) * n + y))
                                break;
                            dp[x][y][0]++;
                        }

                    res = min(res, dp[x][y][0]);

                    // x++
                    if (dp[x + 1][y][1])
                        dp[x][y][1] = dp[x + 1][y][1] + 1;
                    else
                        for (int dis = 1; dis < n - x; dis++)
                        {
                            if (bans.count((x + dis) * n + y))
                                break;

                            dp[x][y][1]++;
                        }
                    res = min(res, dp[x][y][1]);

                    // y--
                    if (dp[x][y + 1][2])
                    {
                        dp[x][y][2] = dp[x][y + 1][2] - 1;
                    }
                    else
                        for (int dis = 1; dis <= y; dis++)
                        {
                            if (bans.count(x * n + y - dis))
                                break;
                            dp[x][y][2]++;
                        }
                    res = min(res, dp[x][y][2]);

                    // y++
                    if (dp[x][y + 1][3])
                    {
                        dp[x][y][3] = dp[x][y + 1][3] + 1;
                    }
                    else
                        for (int dis = 1; dis < n - y; dis++)
                        {
                            if (bans.count(x * n + y + dis))
                                break;
                            dp[x][y][3]++;
                        }
                    res = min(res, dp[x][y][3]);

                    ans = max(ans, res);
                    if (ans == mid - i + 1)
                        return ans;
                }
                if (j)
                {
                    x = mid - i;
                    y = mid + j;
                    res = n;
                    if (!bans.count(x * n + y))
                    {
                        dp[x][y] = {1, 1, 1, 1};
                        int res = n;
                        // x-- 方向
                        if (dp[x + 1][y][0])
                        {
                            dp[x][y][0] = dp[x + 1][y][0] - 1;
                        }
                        else
                            for (int dis = 1; dis <= x; dis++)
                            {
                                if (bans.count((x - dis) * n + y))
                                    break;
                                dp[x][y][0]++;
                            }

                        res = min(res, dp[x][y][0]);

                        // x++
                        if (dp[x - 1][y][1])
                        {
                            dp[x][y][1] = dp[x + 1][y][1] + 1;
                        }
                        else
                            for (int dis = 1; dis < n - x; dis++)
                            {
                                if (bans.count((x + dis) * n + y))
                                    break;

                                dp[x][y][1]++;
                            }
                        res = min(res, dp[x][y][1]);

                        // y--
                        if (dp[x][y - 1][2])
                        {
                            dp[x][y][2] = dp[x][y - 1][2] + 1;
                        }
                        else
                            for (int dis = 1; dis <= y; dis++)
                            {
                                if (bans.count(x * n + y - dis))
                                    break;
                                dp[x][y][2]++;
                            }
                        res = min(res, dp[x][y][2]);

                        // y++
                        if (dp[x][y - 1][3])
                        {
                            dp[x][y][3] = dp[x][y - 1][3] - 1;
                        }
                        else
                            for (int dis = 1; dis < n - y; dis++)
                            {
                                if (bans.count(x * n + y + dis))
                                    break;
                                dp[x][y][3]++;
                            }
                        res = min(res, dp[x][y][3]);

                        ans = max(ans, res);
                        if (ans == mid - i + 1)
                            return maxres;
                    }
                }

                if (i)
                {
                    x = mid + i;
                    y = mid - j;
                    res = n;

                    if (!bans.count(x * n + y))
                    {
                        dp[x][y] = {1, 1, 1, 1};
                        int res = n;
                        // x-- 方向
                        if (dp[x - 1][y][0])
                        {
                            dp[x][y][0] = dp[x - 1][y][0] + 1;
                        }
                        else
                            for (int dis = 1; dis <= x; dis++)
                            {
                                if (bans.count((x - dis) * n + y))
                                    break;
                                dp[x][y][0]++;
                            }

                        res = min(res, dp[x][y][0]);

                        // x++
                        if (dp[x - 1][y][1])
                        {
                            dp[x][y][1] = dp[x - 1][y][1] - 1;
                        }
                        else
                            for (int dis = 1; dis < n - x; dis++)
                            {
                                if (bans.count((x + dis) * n + y))
                                    break;

                                dp[x][y][1]++;
                            }
                        res = min(res, dp[x][y][1]);

                        // y--
                        if (dp[x][y + 1][2])
                        {
                            dp[x][y][2] = dp[x][y + 1][2] - 1;
                        }
                        else
                            for (int dis = 1; dis <= y; dis++)
                            {
                                if (bans.count(x * n + y - dis))
                                    break;
                                dp[x][y][2]++;
                            }
                        res = min(res, dp[x][y][2]);

                        // y++
                        if (dp[x][y + 1][3])
                        {
                            dp[x][y][3] = dp[x][y + 1][3] + 1;
                        }
                        else
                            for (int dis = 1; dis < n - y; dis++)
                            {
                                if (bans.count(x * n + y + dis))
                                    break;
                                dp[x][y][3]++;
                            }
                        res = min(res, dp[x][y][3]);

                        ans = max(ans, res);
                        if (ans == mid - i + 1)
                            return ans;
                    }
                    if (j)
                    {
                        x = mid + i;
                        y = mid + j;
                        res = n;

                        if (!bans.count(x * n + y))
                        {
                            dp[x][y] = {1, 1, 1, 1};
                            int res = n;
                            // x-- 方向
                            if (dp[x - 1][y][0])
                            {
                                dp[x][y][0] = dp[x - 1][y][0] + 1;
                            }
                            else
                                for (int dis = 1; dis <= x; dis++)
                                {
                                    if (bans.count((x - dis) * n + y))
                                        break;
                                    dp[x][y][0]++;
                                }

                            res = min(res, dp[x][y][0]);

                            // x++
                            if (dp[x - 1][y][1])
                            {
                                dp[x][y][1] = dp[x - 1][y][1] - 1;
                            }
                            else
                                for (int dis = 1; dis < n - x; dis++)
                                {
                                    if (bans.count((x + dis) * n + y))
                                        break;

                                    dp[x][y][1]++;
                                }
                            res = min(res, dp[x][y][1]);

                            // y--
                            if (dp[x][y - 1][2])
                            {
                                dp[x][y][2] = dp[x][y - 1][2] + 1;
                            }
                            else
                                for (int dis = 1; dis <= y; dis++)
                                {
                                    if (bans.count(x * n + y - dis))
                                        break;
                                    dp[x][y][2]++;
                                }
                            res = min(res, dp[x][y][2]);

                            // y++
                            if (dp[x][y - 1][3])
                            {
                                dp[x][y][3] = dp[x][y - 1][3] - 1;
                            }
                            else
                                for (int dis = 1; dis < n - y; dis++)
                                {
                                    if (bans.count(x * n + y + dis))
                                        break;
                                    dp[x][y][3]++;
                                }
                            res = min(res, dp[x][y][3]);

                            ans = max(ans, res);
                            if (ans == mid - i + 1)
                                return ans;
                        }
                    }
                }
            }
        }
        return ans;
    }
};
// @lc code=end
