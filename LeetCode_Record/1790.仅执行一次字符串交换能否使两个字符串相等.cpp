#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1790 lang=cpp
 *
 * [1790] 仅执行一次字符串交换能否使两个字符串相等
 */

// @lc code=start
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int n = s1.size();
        char a = ' ', b = ' ';
        for(int i = 0; i < n;i++)
        {
            if(s1[i] != s2[i])
            {
                if(a == '0')
                    return false;
                if(a != ' ')
                {
                    if(s1[i] != b || s2[i] != a)
                        return false;
                    else
                        a = '0';
                }
                else
                    a = s1[i], b = s2[i];
            }
        }
        return a == '0' || a ==' ';
    }
};
// @lc code=end

