#include<vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=667 lang=cpp
 *
 * [667] 优美的排列 II
 */

// @lc code=start
class Solution {
public:
    //distance in (): 1, 1+k(k), 2(k-1), 2 + k - 2(k-2), 3(k-3),..(1), (因为1+k有了)k + 2, k+3,..n   
    vector<int> constructArray(int n, int k) {
        vector<int> ans(n);
        int i = 1;
        ans[0] = 1;
        int sign = 1;
        while(k)
        {
            ans[i++] = ans[i-1] + sign * k--;
            sign *= -1;
        }
        while( i < n)
        {
            ans[i++] = i + 1;
        }
        return ans;
    }
};
// @lc code=end

