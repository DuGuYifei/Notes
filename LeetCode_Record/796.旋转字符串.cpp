#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=796 lang=cpp
 *
 * [796] 旋转字符串
 */

// @lc code=start
class Solution {
public:
    bool rotateString(string s, string goal) {
        // int n =s.size();
        // for(int i = 0;i<n;i++)
        // {
        //     s = s.substr(1,n-1) + s[0];
        //     if(s == goal)
        //         return true;
        // }
        // return false;
        return s.size() == goal.size() && (s+s).find(goal) != string::npos;
    }
};
// @lc code=end

