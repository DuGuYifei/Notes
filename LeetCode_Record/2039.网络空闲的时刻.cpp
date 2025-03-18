#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=2039 lang=cpp
 *
 * [2039] 网络空闲的时刻
 */

// @lc code=start
class Solution
{
public:
    // 单纯BFS然后找到所有节点最短路径, 并同时维护最长用时
    int networkBecomesIdle(vector<vector<int>> &edges, vector<int> &patience)
    {
        int size = patience.size();
        vector<bool> visited(size, false);
        vector<vector<int>> link(size);
        int ans = 0;
        queue<int> waitingVist;

        int dist = 0;
        waitingVist.push(0);
        visited[0] = true;
        for (auto &i : edges)
        {
            link[i[0]].push_back(i[1]);
            link[i[1]].push_back(i[0]);
        }

        while (!waitingVist.empty())
        {
            dist++;
            int n = waitingVist.size();
            for (int i = 0; i < n; i++)
            {
                int visiting = waitingVist.front();
                waitingVist.pop();
                for(int& j:link[visiting])
                {
                    if(visited[j])
                    {
                        continue;
                    }
                    waitingVist.push(j);
                    visited[j] = true;
                    ans = max(ans,  patience[j] * ((2 * dist - 1) / patience[j]) + 2 * dist + 1);
                }
            }
        }

        return ans;
    }
};
// @lc code=end
