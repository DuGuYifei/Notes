#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=944 lang=cpp
 *
 * [944] 删列造序
 */

// @lc code=start
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int ans = 0;
        int n = strs.size();
        for(int i = 0;i < 1000;i++)
        {
            int rows = 0;
            char temp = '\0';
            for(const string& s:strs)
            {
                if(s.size()< i + 1)
                {
                    rows += 1;
                    if(rows == n)
                        return ans;
                    continue;
                }
                if(s[i] < temp)
                {
                    ans++;
                    break;
                }
                temp = s[i];
            }
        }
        return ans;
    }
};
// @lc code=end

