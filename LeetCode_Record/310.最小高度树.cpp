#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=310 lang=cpp
 *
 * [310] 最小高度树
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> tree;
    vector<int> parent;
    int longestNode(int root, int n)
    {
        queue<int> wait;
        wait.push(root);
        int node;
        vector<int> p(n, -1);
        while (!wait.empty())
        {
            int n = wait.size();
            for (int i = 0; i < n; i++)
            {
                // x不需要同一行的其他元素，因为它们都会连接到相同的上一级节点，经过的中间路径是一样的
                // 如果是另一个支的相同高度节点，也基本就是到这个节点最长的另一端了。
                node = wait.front();
                for (int &child : tree[node])
                {
                    if (child == p[node])
                        continue;
                    p[child] = node;
                    wait.push(child);
                }
                wait.pop();
            }
        }
        parent = p;
        return node;
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        if(n == 1)
            return vector<int>{0};
        tree = vector<vector<int>>(n);
        // 最小高度 = 最长距离/2
        for (vector<int> &i : edges)
        {
            tree[i[0]].push_back(i[1]);
            tree[i[1]].push_back(i[0]);
        }
        int x_node = longestNode(edges[0][0], n);
        int y_node = longestNode(x_node, n);
        vector<int> path;
        while (y_node != -1) // 根节点的 parent[root]  -1
        {
            path.push_back(y_node);
            y_node = parent[y_node];
        }
        int s = path.size();
        if (s % 2)
        {
            return vector<int>{path[s / 2]};
        }
        return vector<int>{path[s / 2 - 1], path[s / 2]};
    }
};
// @lc code=end
