#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1129 lang=cpp
 *
 * [1129] 颜色交替的最短路径
 *
 * https://leetcode-cn.com/problems/shortest-path-with-alternating-colors/description/
 *
 * algorithms
 * Medium (39.04%)
 * Likes:    130
 * Dislikes: 0
 * Total Accepted:    11.5K
 * Total Submissions: 27.6K
 * Testcase Example:  '3\n[[0,1],[1,2]]\n[]'
 *
 * 在一个有向图中，节点分别标记为 0, 1, ..., n-1。图中每条边为红色或者蓝色，且存在自环或平行边。
 *
 * red_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的红色有向边。类似地，blue_edges 中的每一个 [i, j]
 * 对表示从节点 i 到节点 j 的蓝色有向边。
 *
 * 返回长度为 n 的数组 answer，其中 answer[X] 是从节点 0 到节点 X
 * 的红色边和蓝色边交替出现的最短路径的长度。如果不存在这样的路径，那么 answer[x] = -1。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
 * 输出：[0,1,-1]
 *
 *
 * 示例 2：
 *
 *
 * 输入：n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
 * 输出：[0,1,-1]
 *
 *
 * 示例 3：
 *
 *
 * 输入：n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
 * 输出：[0,-1,-1]
 *
 *
 * 示例 4：
 *
 *
 * 输入：n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
 * 输出：[0,1,2]
 *
 *
 * 示例 5：
 *
 *
 * 输入：n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
 * 输出：[0,1,1]
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= n <= 100
 * red_edges.length <= 400
 * blue_edges.length <= 400
 * red_edges[i].length == blue_edges[i].length == 2
 * 0 <= red_edges[i][j], blue_edges[i][j] < n
 *
 *
 */

// @lc code=start
class Solution
{
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges)
    {
        unordered_map<int, vector<int>> redges;
        unordered_map<int, vector<int>> bedges;
        for (auto &i : redEdges)
        {
            redges[i[0]].push_back(i[1]);
        }
        for (auto &i : blueEdges)
        {
            bedges[i[0]].push_back(i[1]);
        }
        queue<int> visited_red;
        queue<int> visited_blue;
        vector<int> visited_color(n); // 0 no visit, 01 blue, 10 red, 11 both
        vector<int> dismap(n, -1);
        visited_color[0] = 3;
        for (auto &i : redges[0])
        {
            visited_red.emplace(i);
            dismap[i] = 1;
            visited_color[i] |= 2;
        }
        for (auto &i : bedges[0])
        {
            visited_blue.emplace(i);
            dismap[i] = 1;
            visited_color[i] |= 1;
        }
        dismap[0] = 0;
        int dis = 2;
        while (!(visited_blue.empty() && visited_red.empty()))
        {
            int nr = visited_red.size();
            int nb = visited_blue.size();
            while (nr > 0)
            {
                nr--;
                int t = visited_red.front();
                visited_red.pop();
                for (int &next : bedges[t])
                {
                    if ((visited_color[next] & 1) == 1)
                        continue;
                    visited_color[next] |= 1;
                    visited_blue.emplace(next);
                    if (dismap[next] == -1)
                        dismap[next] = dis;
                }
            }
            while (nb > 0)
            {
                nb--;
                int t = visited_blue.front();
                visited_blue.pop();
                for (int &next : redges[t])
                {
                    if ((visited_color[next] & 2) == 2)
                        continue;
                    visited_color[next] |= 2;
                    visited_red.emplace(next);
                    if (dismap[next] == -1)
                        dismap[next] = dis;
                }
            }
            dis++;
        }

        return dismap;
    }
};
// @lc code=end
