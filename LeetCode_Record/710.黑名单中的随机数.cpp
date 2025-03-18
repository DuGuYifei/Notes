#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=710 lang=cpp
 *
 * [710] 黑名单中的随机数
 */

// @lc code=start
class Solution
{
public:
    int bound;
    unordered_map<int, int> b2w;
    Solution(int n, vector<int> &blacklist)
    {
        int m = blacklist.size();
        bound = n - m;

        int w = bound;
        unordered_set<int> black;
        for (auto &i : blacklist)
        {
            if(i >= w)
                black.emplace(i);
        }
        for (auto &i : blacklist)
        {
            if (i < bound)
            {
                while (black.count(w))
                {
                    ++w;
                }
                b2w[i] = w++;
            }
        }
    }

    int pick()
    {
        int x = rand()%bound;
        return b2w.count(x)?b2w[x]:x;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
// @lc code=end
