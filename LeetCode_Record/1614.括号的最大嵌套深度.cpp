#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1614 lang=cpp
 *
 * [1614] 括号的最大嵌套深度
 */

// @lc code=start
class Solution
{
public:
    int maxDepth(string s)
    {
        // int depth = 0;
        // int maxDepth = 0;
        // int left = 0;
        // int signs = 0;
        // for (int i = 0; i < s.length(); i++)
        // {
        //     if (s[i] == '(')
        //     {
        //         left++;
        //         if (signs > 0)
        //         {
        //             if (depth > 0)
        //             {
        //                 maxDepth = max(depth, maxDepth);
        //                 depth--;
        //             }
        //         }
        //     }
        //     else if (s[i] == ')' && left > 0)
        //     {
        //         left--;
        //         depth++;
        //         if (left == 0)
        //         {
        //             maxDepth = max(depth, maxDepth);
        //             depth = 0;
        //         }
        //     }
        //     else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] =='/')
        //     {
        //         signs++;
        //     }
        // }

        /*************************************************
         * 已经被保证是VPS了
        *************************************************/

        int depth = 0;
        int maxDepth = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
            {
                depth++;
                maxDepth = max(depth, maxDepth);
            }
            else if (s[i] == ')')
            {
                depth--;
            }
        }

        return maxDepth;
    }
};
// @lc code=end
