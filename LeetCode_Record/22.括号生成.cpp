#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        string cur = "";
        vector<string> ans;
        dfs(cur, 0, n, ans);
        return ans;
    }
    void dfs(string &cur, int remainRight, int remainLeft, vector<string> &ans)
    {
        if (remainLeft == 0 && remainRight == 0)
        {
            ans.push_back(cur);
            return;
        }
        if (remainLeft != 0)
        {
            cur.push_back('(');
            dfs(cur, remainRight+1, remainLeft-1, ans);
            cur.pop_back();
        }
        if (remainRight > 0)
        {
            cur.push_back(')');
            dfs(cur, remainRight-1, remainLeft, ans);
            cur.pop_back();
        }
    }
};
// @lc code=end
