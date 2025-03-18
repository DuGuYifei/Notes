#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1694 lang=cpp
 *
 * [1694] 重新格式化电话号码
 */

// @lc code=start
class Solution {
public:
    string reformatNumber(string number) {
        string ans = "";
        int cnt = 0;
        for(char& i: number)
        {
            if(i >= '0')
            {
                ans.push_back(i);
                cnt++;
            }
            if(cnt == 3)
            {
                ans.push_back('-');
                cnt = 0;
            }
        }
        if(cnt == 1)
        {
            int n = ans.size();
            ans[n - 2] = ans[n - 3];
            ans[n - 3] = '-';
        }
        else if(cnt == 0)
            ans.pop_back();
        return ans;
    }
};
// @lc code=end

