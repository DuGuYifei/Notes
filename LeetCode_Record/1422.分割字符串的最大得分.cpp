#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1422 lang=cpp
 *
 * [1422] 分割字符串的最大得分
 */

// @lc code=start
class Solution {
public:
    int maxScore(string s) {
        int num0 = 0;
        int num1 = 0;
        for(char& i : s)
        {
            if(i == '0')
                num0++;
            else
                num1++;
        }
        int ans = 0;
        int score = num1;
        for(int i = 0; i < s.size() - 1; i++)
        {
            if(s[i] == '0')
            {
                score++;
            }
            else
            {
                score--;
            }
            ans = max(score, ans);
        }
        return ans;
    }
};
// @lc code=end

