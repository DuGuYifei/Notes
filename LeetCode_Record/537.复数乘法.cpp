#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=537 lang=cpp
 *
 * [537] 复数乘法
 */

// @lc code=start
class Solution {
public:
    string complexNumberMultiply(string num1, string num2) {
        string a = "", b="", c="", d="";
        int i = 0;
        while(num1[i]!='+')
        {
            a+=num1[i];
            i++;
        }
        i++;
        while(num1[i]!='i')
        {
            b+=num1[i];
            i++;
        }

        i = 0;
        while(num2[i]!='+')
        {
            c+=num2[i];
            i++;
        }
        i++;
        while(num2[i]!='i')
        {
            d+=num2[i];
            i++;
        }
        int aa,bb,cc,dd;
        aa = atoi(a.c_str());
        bb = atoi(b.c_str());
        cc = atoi(c.c_str());
        dd = atoi(d.c_str());
        string ans = to_string(aa*cc - bb*dd) + "+" +  to_string(aa*dd+bb*cc) + "i";
        return ans;
    }
};
// @lc code=end

