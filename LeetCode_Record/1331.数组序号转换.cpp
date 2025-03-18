#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1331 lang=cpp
 *
 * [1331] 数组序号转换
 */

// @lc code=start
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        int n = arr.size();
        vector<int> idx(n,0);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), 
            //[&arr]
            [r = arr.data()]
            (int a, int b)
            {return r[a] < r[b];});
            //{return arr[a] < arr[b];});

        int rank = 0;
        int prev = INT_MIN;
        for(int& i : idx)
        {
            if(arr[i] != prev) 
                rank++;
            prev = arr[i];
            arr[i] = rank;
        }
        return arr;
    }
};
// @lc code=end

