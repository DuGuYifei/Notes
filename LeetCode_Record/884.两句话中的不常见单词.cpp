#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;
/*
 * @lc app=leetcode.cn id=884 lang=cpp
 *
 * [884] 两句话中的不常见单词
 */

// @lc code=start
class Solution
{
public:
    vector<string> uncommonFromSentences(string s1, string s2)
    {
        unordered_map<string, int> words;
        s1.append(1,' ');
        s1.append(s2);
        stringstream ss(s1);
        string s;
        vector<string> res;
        while (ss >> s)
        {
            words[move(s)]++;
        }
        for (const auto &[k, v] : words)
        {
            if (v == 1)
                res.push_back(move(k));
        }
        return res;
    }
};
// @lc code=end
