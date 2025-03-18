#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=824 lang=cpp
 *
 * [824] 山羊拉丁文
 */

// @lc code=start
class Solution
{
public:
    string toGoatLatin(string sentence)
    {
        string ans = "";
        int n = sentence.size();
        int index = 1;
        for (int i = 0; i < n; i++)
        {
            char c = sentence[i];
            string tail = "";
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            {
                tail = "ma";
                tail.append(index, 'a');
            }
            else
            {
                tail = string(1, c) + "ma";
                tail.append(index, 'a');
                i++;
                if (i == n)
                    return ans + tail;
                c = sentence[i];
            }
            index++;

            while (c != ' ')
            {
                ans.append(1, c);
                i++;
                if (i == n)
                    return ans + tail;
                c = sentence[i];
            }
            ans += tail;
            ans += " ";
        }
        return ans;
    }
};
// @lc code=end
