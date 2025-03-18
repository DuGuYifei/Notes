#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=436 lang=cpp
 *
 * [436] 寻找右区间
 */

// @lc code=start
class Solution
{
public:
    vector<int> findRightInterval(vector<vector<int>> &intervals)
    {
        vector<pair<int, int>> start;
        vector<pair<int, int>> end;
        int n = intervals.size();
        for (int i = 0; i < n; i++)
        {
            start.push_back(pair<int, int>{intervals[i][0], i});
            end.push_back(pair<int, int>{intervals[i][1], i});
        }
        sort(start.begin(), start.end());
        sort(end.begin(), end.end());
        vector<int> ans(n, -1);
        int indexStart = 0;
        for (int indexEnd = 0; indexEnd < n; indexEnd++)
        {
            while (start[indexStart].first < end[indexEnd].first)
            {
                indexStart++;
                if(indexStart == n)
                    return ans;
            }
            ans[end[indexEnd].second] = start[indexStart].second;
        }
        return ans;
    }
};
// @lc code=end
