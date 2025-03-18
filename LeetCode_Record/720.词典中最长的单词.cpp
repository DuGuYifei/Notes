#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=720 lang=cpp
 *
 * [720] 词典中最长的单词
 */

// @lc code=start
class Solution
{
public:
    // 优先按照size升序，相同size再按字母降序
    string longestWord(vector<string> &words)
    {
        string ans = "";
        sort(words.begin(), words.end(), [](const string &a, const string &b)
             {
                int x = a.size(), y = b.size();
                if (x != y)
                {
                    return x < y;
                }
                return a > b; 
             });
        unordered_set<string> dict;
        for (string &i : words)
        {
            int size = i.size();
            if (size == 1)
            {
                dict.emplace(i);
                ans = i;
                continue;
            }
            if (dict.count(i.substr(0, size - 1)))
            {
                dict.emplace(i);
                ans = i;
            }
        }
        return ans;
    }
};
// @lc code=end
