#include <unordered_set>
using namespace std;
/*
 * @lc app=leetcode.cn id=804 lang=cpp
 *
 * [804] 唯一摩尔斯密码词
 */

// @lc code=start
const static string MORSE[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        "....", "..", ".---", "-.-", ".-..", "--", "-.",
        "---", ".--.", "--.-", ".-.", "...", "-", "..-",
        "...-", ".--", "-..-", "-.--", "--.."
};
class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        unordered_set<string> translation;
        for(auto& i : words)
        {
            string trans = "";
            for(auto& j : i)
            {
                trans += MORSE[j - 'a'];
            }
            translation.emplace(trans);
        }
        return translation.size();
    }
};
// @lc code=end

