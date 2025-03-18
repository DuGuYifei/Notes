#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
// class Solution
// {
// public:
//     unordered_map<char, string> phone = {
//         {'2', "abc"},
//         {'3', "def"},
//         {'4', "ghi"},
//         {'5', "jkl"},
//         {'6', "mno"},
//         {'7', "pqrs"},
//         {'8', "tuv"},
//         {'9', "wxyz"}};
//     vector<string> ans;
//     vector<string> letterCombinations(string digits)
//     {
//         if (digits == "")
//             return {};

//         for (char &i : phone[digits[0]])
//         {
//             string item = "";
//             item.append(1, i);
//             dfs(1, digits, item);
//         }
//         return ans;
//     }
//     void dfs(int index, string &digits, string item)
//     {
//         if (digits[index] == '\0')
//         {
//             ans.push_back(item);
//             return;
//         }
//         for (char &i : phone[digits[index]])
//         {
//             string newItem = item;
//             newItem.append(1, i);
//             dfs(index + 1, digits, newItem);
//         }
//     }
// };
class Solution
{
public:
    const string phone[10] = {
            "", // 0
            "", // 1
            "abc", // 2
            "def", // 3
            "ghi", // 4
            "jkl", // 5
            "mno", // 6
            "pqrs", // 7
            "tuv", // 8
            "wxyz", // 9
        };
    vector<string> ans;
    vector<string> letterCombinations(string digits)
    {
        if (digits == "")
            return {};

        for (const char &i : phone[digits[0]-'0'])
        {
            string item = "";
            item.append(1, i);
            dfs(1, digits, item);
        }
        return ans;
    }
    void dfs(int index, string &digits, string item)
    {
        if (digits[index] == '\0')
        {
            ans.push_back(item);
            return;
        }
        for (const char &i : phone[digits[index]-'0'])
        {
            string newItem = item;
            newItem.append(1, i);
            dfs(index + 1, digits, newItem);
        }
    }
};
// @lc code=end
