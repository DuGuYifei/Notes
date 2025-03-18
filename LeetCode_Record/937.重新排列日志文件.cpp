#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=937 lang=cpp
 *
 * [937] 重新排列日志文件
 */

// @lc code=start
class Solution {
public:
    static bool cmp(const string& a, const string& b)
    {
        int posa = a.find_first_of(' ');
        int posb = b.find_first_of(' ');
        bool ad = isdigit(a[posa+1]);
        bool bd = isdigit(b[posb+1]);
        if(ad && bd)
        {
            return false;
        }
        if(!ad && !bd)
        {
            string sa = a.substr(posa+1);
            string sb = b.substr(posb+1);
            if(sa!=sb)
            {
                return sa < sb;
            }
            return a<b;
        }
        return ad? false:true;
    }
    vector<string> reorderLogFiles(vector<string>& logs) {
        stable_sort(logs.begin(),logs.end(),cmp);
        return logs;
    }
};
// @lc code=end

