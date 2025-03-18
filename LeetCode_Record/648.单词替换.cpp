#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=648 lang=cpp
 *
 * [648] 单词替换
 */

// @lc code=start
struct Tire
{
    unordered_map<char, Tire *> dict;
};

class Solution
{
public:
    string replaceWords(vector<string> &dictionary, string sentence)
    {
        // 方法一
        // unordered_set<string_view> dict;
        // for(const auto& i : dictionary)
        // {
        //     dict.emplace(i);
        // }
        // int start = 0;
        // string res = "";
        // int n = sentence.size();
        // for(int i = 0; i <= n; i++)
        // {
        //     if(sentence[i] == ' ' || i == n)
        //     {
        //         res += sentence.substr(start, i - start);
        //         res += " ";
        //         start = i + 1;
        //         continue;
        //     }
        //     string rootTest = sentence.substr(start, i - start + 1);
        //     if(dict.count(rootTest))
        //     {
        //         res += rootTest;
        //         res += " ";
        //         while(sentence[i] != ' ' && i != n)
        //         {
        //             i++;
        //         }
        //         start = i + 1;
        //         continue;
        //     }
        // }
        // res.pop_back();
        // return res;

        // 方法二：字典树，前缀树

        //输入字典
        Tire* root = new Tire();
        for (auto& word : dictionary)
        {
            Tire* cur = root;
            for (char& i : word)
            {
                if (!cur->dict.count(i))
                    cur->dict[i] = new Tire();
                cur = cur->dict[i];
            }
            cur->dict['#'] = new Tire();
        }

        int start = 0;
        string res = "";
        int n = sentence.size();
        for (int i = 0; i < n; i++)
        {
            Tire* cur = root;
            while (i < n && sentence[i] != ' ')
            {
                if (cur->dict.count('#'))
                {
                    res += sentence.substr(start, i - start);
                    res += " ";
                    while (sentence[i] != ' ' && i != n)
                        i++;
                    start = ++i;
                    cur = root;
                }
                else if (!cur->dict.count(sentence[i]))
                {
                    while (sentence[i] != ' ' && i != n)
                        i++;
                    res += sentence.substr(start, i - start);
                    res += " ";
                    start = ++i;
                    cur = root;
                }
                else
                {
                    cur = cur->dict[sentence[i]];
                    i++;
                    if (i == n)
                    {
                        return res += sentence.back();
                    }
                }
            }
        }
        res.pop_back();
        return res;
    }
};
// @lc code=end
