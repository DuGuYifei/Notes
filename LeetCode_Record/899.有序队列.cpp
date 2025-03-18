/*
 * @lc app=leetcode.cn id=899 lang=cpp
 *
 * [899] 有序队列
 */

// @lc code=start
class Solution
{
public:
    string orderlyQueue(string s, int k)
    {
        if (k != 1)
        {
            sort(s.begin(), s.end());
            return s;
        }
        string ans = s;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            s = s.substr(1, n - 1) + s[0];
            ans = min(s, ans);
        }
        return ans;
    }
};
// @lc code=end
