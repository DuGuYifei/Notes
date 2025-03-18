#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=917 lang=cpp
 *
 * [917] 仅仅反转字母
 */

// @lc code=start
class Solution
{
public:
    string reverseOnlyLetters(string s)
    {
        int i = 0;
        int j = s.size() - 1;
        while (i < j)
        {
            if (!(s[i] >= 65 && s[i] <= 90 || s[i] >= 97 && s[i] <= 122))
            {
                i++;
                continue;
            }
            if (!(s[j] >= 65 && s[j] <= 90 || s[j] >= 97 && s[j] <= 122))
            {
                j--;
                continue;
            }
            char temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        }
        return s;
    }
};
// @lc code=end
