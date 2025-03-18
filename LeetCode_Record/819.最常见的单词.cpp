#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=819 lang=cpp
 *
 * [819] 最常见的单词
 */

// @lc code=start
class Solution
{
public:
    string mostCommonWord(string paragraph, vector<string> &banned)
    {
        unordered_set<string> ban;
        unordered_map<string, int> words;
        for (auto &i : banned)
        {
            ban.emplace(i);
        }
        string word;
        string maxWords;
        int maxfre = 0;
        for (int i = 0; i < paragraph.size(); i++)
        {
            if (isalpha(paragraph[i]))
            {
                word += tolower(paragraph[i]);
            }
            else
            {
                if (word != "")
                {
                    if (!ban.count(word))
                    {
                        words[word]++;
                        if (words[word] > maxfre)
                        {
                            maxWords = word;
                            maxfre = words[word];
                        }
                    }
                    word = "";
                }
            }
        }
        // 以单词结尾
        if (word != "")
        {
            if (!ban.count(word))
            {
                words[word]++;
                if (words[word] > maxfre)
                {
                    maxWords = word;
                    maxfre = words[word];
                }
            }
        }
        return maxWords;
    }
};
// @lc code=end
