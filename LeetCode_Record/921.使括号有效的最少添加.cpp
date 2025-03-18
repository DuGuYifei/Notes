#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=921 lang=cpp
 *
 * [921] 使括号有效的最少添加
 */

// @lc code=start
class Solution {
public:
    int minAddToMakeValid(string s) {
        int left = 0;
        int ans = 0;
        for(auto& i : s)
        {
            if(i == '(')
                left++;
            else{
                if(left)
                    left--;
                else
                    ans++;
            }
        }
        return ans + left;
    }
};
// @lc code=end

