#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=682 lang=cpp
 *
 * [682] 棒球比赛
 */

// @lc code=start
class Solution
{
public:
    int calPoints(vector<string> &ops)
    {
        int ans = 0;
        vector<int> points;
        int temp;
        int n;
        for (string& op:ops)
        {
            switch (op[0])
            {
            case '+':
                n = points.size();
                temp = points[n - 1] + points[n - 2];
                points.push_back(temp);
                ans += temp;
                break;
            case 'D':
                temp = 2 * points[points.size() - 1];
                points.push_back(temp);
                ans += temp;
                break;
            case 'C':
                ans -= points[points.size() - 1];
                points.pop_back();
                break;
            default:
                temp = stoi(op);
                points.push_back(temp);
                ans += temp;
                break;
            }
        }
        return ans;
    }
};
// @lc code=end
