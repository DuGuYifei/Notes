#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=942 lang=cpp
 *
 * [942] 增减字符串匹配
 */

// @lc code=start
class Solution {
public:
    vector<int> diStringMatch(string s) {
        int right = s.size();
        int left = 0;
        vector<int>ans;
        for(auto& i: s)
        {
            if(i == 'I')
            {
                ans.push_back(left++);
            }
            else
            {
                ans.push_back(right--);
            }
        }
        ans.push_back(left);
        return ans;
    }
};
// @lc code=end

