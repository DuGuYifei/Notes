#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2049 lang=cpp
 *
 * [2049] 统计最高分的节点数目
 */

// @lc code=start
class Solution
{
public:
    int size;
    long maxScore = 0;
    int ans = 0;

    // 返回值是向下遍历了多少，相当于已知下面两个分支分别还有多少，再用size减去得到上面有多少
    int dfs(vector<vector<int>> &children, int index)
    {
        long product = 1;
        int n = 1;
        for (int &child : children[index])
        {
            int temp = dfs(children, child);
            product *= (long)temp;

            n += temp;
        }
        // n++;
        long temp = size - n;
        if (temp != 0)
            product *= temp;
        if (product > maxScore)
        {
            maxScore = product;
            ans = 1;
        }
        else if (product == maxScore)
            ans++;
        return n;
    }

    int countHighestScoreNodes(vector<int> &parents)
    {
        size = parents.size();
        vector<vector<int>> children(size);
        for (int i = 1; i < size; i++)
        {
            children[parents[i]].push_back(i);
        }
        dfs(children, 0);
        return ans;
    }
};
// @lc code=end
