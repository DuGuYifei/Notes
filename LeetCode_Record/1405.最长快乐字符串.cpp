#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1405 lang=cpp
 *
 * [1405] 最长快乐字符串
 */

// @lc code=start
// ccaccaccabb
// ccbbaccbacca
class Solution
{
public:
    string longestDiverseString(int a, int b, int c)
    {
        pair<int, char> alphabet[3] = {{a, 'a'}, {b, 'b'}, {c, 'c'}};
        string s = "";
        while (true)
        {
            sort(alphabet, alphabet + 3);
            int n = s.size();
            if (n >= 2 && s[n - 1] == s[n - 2] && s[n - 1] == alphabet[2].second)
            {
                if (alphabet[1].first == 0)
                    break;
                s.append(1, alphabet[1].second);
                alphabet[1].first--;
            }
            else
            {
                if (alphabet[2].first == 0)
                    break;
                s.append(1, alphabet[2].second);
                alphabet[2].first--;
            }
        }
        return s;
    }
};
// @lc code=end
