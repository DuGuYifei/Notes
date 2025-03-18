#include<vector>
#include<algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=646 lang=cpp
 *
 * [646] 最长数对链
 */

// @lc code=start
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end(), [](const vector<int>&a, const vector<int>&b){
            return a[0]>b[0];
        });
        int ans = 0;
        int num = INT_MAX;
        for(auto& i : pairs)
        {
            if(i[1] < num)
            {
                ans++;
                num = i[0];
            }
        }
        return ans;
    }
};
// @lc code=end

