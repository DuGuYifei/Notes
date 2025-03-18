#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=521 lang=cpp
 *
 * [521] 最长特殊序列 Ⅰ
 */

// @lc code=start
class Solution {
public:
    int findLUSlength(string a, string b) {
        // int n1 = a.size();
        // int n2 = b.size();
        // if(n1 > n2) return n1;
        // if(n2 > n1) return n2;
        // for(int i = 0; i < n1 ; i++)
        // {
        //     if(a[i]!=b[i])
        //         return n1;
        // }
        // return -1;
        if(a == b) return -1;
        else return max(a.size(), b.size());
    }
};
// @lc code=end

