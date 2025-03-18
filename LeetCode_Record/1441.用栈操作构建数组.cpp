#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1441 lang=cpp
 *
 * [1441] 用栈操作构建数组
 */

// @lc code=start
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        int start = 1;
        vector<string> ans;
        for(auto& i : target)
        {
            while(start < i)
            {
                ans.push_back("Push");
                ans.push_back("Pop");
                start++;
            }
            start++;
            ans.push_back("Push");
        }
        return ans;
    }
};
// @lc code=end

