#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=757 lang=cpp
 *
 * [757] 设置交集大小至少为2
 */

// @lc code=start
class Solution
{
public:
    int intersectionSizeTwo(vector<vector<int>> &intervals)
    {
        // 关键点：小interval满足，大的一定满足，所以排序
        // 用后面的两个数放进集合结果是因为如果完全反过来用前面的，那么push到结果v的最前面还得把所有元素往后推
        vector<int> v{-1, -1};
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b)
            {
                return a[1] < b[1] || (a[1] == b[1] && a[0] > b[0]);//先给各个区间排序 
            });
        for (auto &interval : intervals)
        {
            int len = v.size();
            if (interval[0] <= v[len - 2])
                continue; //说明一定有两个重复元素，所以不添加元素也有两个重复的
            if (interval[0] > v.back())
                v.push_back(interval[1] - 1); //说明v数组和当前区间没有一个交集，所以这里取两个最大的元素添加进去
            v.push_back(interval[1]);
        }
        return v.size() - 2;
    }
};
// @lc code=end
