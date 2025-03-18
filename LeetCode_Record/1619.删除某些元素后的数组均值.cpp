#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1619 lang=cpp
 *
 * [1619] 删除某些元素后的数组均值
 */

// @lc code=start
class Solution {
public:
    double trimMean(vector<int>& arr) {
        int n = arr.size();
        int delNum = n * 0.05;
        sort(arr.begin(),arr.end());
        return accumulate(arr.begin() + delNum, arr.end() - delNum, 0) / (n * 0.9);
    }
};
// @lc code=end

