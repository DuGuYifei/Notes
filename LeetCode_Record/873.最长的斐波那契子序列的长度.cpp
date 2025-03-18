#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=873 lang=cpp
 *
 * [873] 最长的斐波那契子序列的长度
 */

// @lc code=start
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        vector<vector<int>> dp(n, vector<int>(n,2));
        unordered_map<int,int> dict;
        for(int i = 0;i < n; i++)
        {
            dict[arr[i]] = i;
        }
        for(int i = 1;i < n - 1; i++)
        {
            for(int j = n - 1; j > i && arr[i] * 2 > arr[j]; j--)
            {
                int k = arr[j] - arr[i];
                if(dict.count(k))
                {
                    dp[i][j] = dp[dict[k]][i]+1;
                    ans = max(dp[i][j], ans);
                }
            }
        }
        return ans > 2? ans:0;
    }
};
// @lc code=end

