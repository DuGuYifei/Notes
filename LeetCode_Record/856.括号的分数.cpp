#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=856 lang=cpp
 *
 * [856] 括号的分数
 */

// @lc code=start
class Solution {
public:
    int scoreOfParentheses(string s) {
        int depth = 0;
        int point = 0;
        bool effect = false;
        int ans = 0;
        for(auto& i:s)
        {
            if(i == '(')
            {
                if(point)
                    point *= 2;
                else
                    point = 1;
                depth++;
                effect = true;
            }
            else{
                depth--;
                if(effect)
                {
                    ans += point;
                    effect = false;
                }
                point /= 2;
            }
        }
        return ans;
    }
};
// @lc code=end

