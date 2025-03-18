#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1784 lang=cpp
 *
 * [1784] 检查二进制字符串字段
 */

// @lc code=start
class Solution {
public:
    bool checkOnesSegment(string s) {
        // int i = 0, n = s.size();
        // while(i < n && s[i] != '1')
        //     i++;
        // if(i == n)
        //     return true;
        // while(i < n && s[i] == '1')
        //     i++;
        // while(i < n && s[i] != '1')
        //     i++;
        // if(i!=n)
        //     return false;
        // return true;
        return s.find("01") == string::npos;
    }
};
// @lc code=end

