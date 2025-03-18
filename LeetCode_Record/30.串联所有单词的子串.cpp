#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */

// @lc code=start

// Method 1:
// 在s上滑动，每次滑word的长度，则左边少一个，右边多一个
class Solution {
public:
    vector<int> findSubstring(string &s, vector<string> &words) {
        vector<int> res;
        int m = words.size(), n = words[0].size(), ls = s.size();
        for (int i = 0; i < n && i + m * n <= ls; ++i) {
            unordered_map<string, int> differ;
            for (int j = 0; j < m; ++j) {
                ++differ[s.substr(i + j * n, n)];
            }
            for (string &word: words) {
                if (--differ[word] == 0) {
                    differ.erase(word);
                }
            }
            for (int start = i; start < ls - m * n + 1; start += n) {
                if (start != i) {
                    string word = s.substr(start + (m - 1) * n, n);
                    if (++differ[word] == 0) {
                        differ.erase(word);
                    }
                    word = s.substr(start - n, n);
                    if (--differ[word] == 0) {
                        differ.erase(word);
                    }
                }
                if (differ.empty()) {
                    res.emplace_back(start);
                }
            }
        }
        return res;
    }
};


// Method 2：
// class Solution
// {
// public:
//     vector<int> findSubstring(string s, vector<string> &words)
//     {
//         vector<int> ans;
//         unordered_map<string, int> dict;
//         int n = s.size();
//         for (auto &i : words)
//         {
//             dict[i]++;
//         }
//         int l = words[0].size();
//         int num = words.size();
//         for (int i = 0; i <= n - l * num; i++)
//         {
//             string t = s.substr(i, l);
//             if (dict[t])
//             {
//                 int num2 = num - 1;
//                 if (num2 == 0)
//                 {
//                     ans.push_back(i);
//                 }
//                 else
//                 {
//                     unordered_map<string, int> dict2 = dict;
//                     dict2[t]--;
//                     int j = i + l;
//                     for (; j <= n - l; j += l)
//                     {
//                         t = s.substr(j, l);
//                         if (dict2[t])
//                         {
//                             dict2[t]--;
//                             num2--;
//                             if (num2 == 0)
//                             {
//                                 ans.push_back(i);
//                                 i = i + l - 1;
//                                 break;
//                             }
//                         }
//                         else
//                         {
//                             break;
//                         }
//                     }
//                 }
//             }
//         }
//         return ans;
//     }
// };
// @lc code=end
