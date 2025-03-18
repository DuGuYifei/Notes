#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1374 lang=cpp
 *
 * [1374] 生成每种字符都是奇数个的字符串
 */

// @lc code=start
class Solution
{
public:
    string generateTheString(int n)
    {
        if (n % 2)
        {
            return string(n, 'a');
        }
        string ans(n - 1, 'a');
        ans.push_back('b');
        return ans;
    }
};
// @lc code=end
