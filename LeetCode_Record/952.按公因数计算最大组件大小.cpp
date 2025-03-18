#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=952 lang=cpp
 *
 * [952] 按公因数计算最大组件大小
 */

// @lc code=start


/* 方法一
class UnionFind
{
private:
    vector<int> parent; // 存放每个数字的parent（parent就是因子），长度不是原数字的长度，而是原数组最大值的长度

public:
    UnionFind(int n)
    {
        parent = vector<int>(n);

        // 先将每个数的parent初始化为自己
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // 因为这是个链型结构，不是每个数直接找到最小的质因数作为parent，而是一层层向前找
    // 比如24父亲是24一开始，然后开始从小到大暴力找parent，找到一个就合并一个
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void uni(int father, int origin)
    {
        int rootx = find(father);
        int rooty = find(origin);
        parent[rooty] = parent[rootx];
    }
};
class Solution
{
public:
    int largestComponentSize(vector<int> &nums)
    {
        int m = *max_element(nums.begin(), nums.end());
        UnionFind un(m + 1);

        for (int &i : nums)
        {
            for (int j = 2; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    un.uni(j, i);
                    un.uni(i / j, i);
                }
            }
        }

        vector<int> counts(m + 1);
        int ans = 0;
        for (auto &i : nums)
        {
            int parent = un.find(i);
            counts[parent] ++;
            ans = max(ans, counts[parent]);
        }
        return ans;
    }
};
*/

//方法二
class UnionFind {
public:
    UnionFind(int n) {
        parent = vector<int>(n);
        rank = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    void uni(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] > rank[rooty]) {
                parent[rooty] = rootx;
            } else if (rank[rootx] < rank[rooty]) {
                parent[rootx] = rooty;
            } else {
                parent[rooty] = rootx;
                rank[rootx]++;
            }
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    vector<int> parent;
    vector<int> rank;
};
class Solution
{
public:
    int largestComponentSize(vector<int> &nums)
    {
        int m = *max_element(nums.begin(), nums.end());
        UnionFind un(m + 1);

        for (int i : nums)
        {
            for (int j = 2; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    un.uni(j, i);
                    un.uni(i / j, i);
                }
            }
        }

        vector<int> counts(m + 1);
        int ans = 0;
        for (int i : nums)
        {
            int parent = un.find(i);
            counts[parent]++;
            ans = max(ans, counts[parent]);
        }
        return ans;
    }
};
// @lc code=end
