#include<vector>
#include<string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1592 lang=cpp
 *
 * [1592] 重新排列单词间的空格
 */

// @lc code=start
class Solution {
public:
    string reorderSpaces(string text) {
        vector<string> words;
        int space = 0;
        int start = -1;
        int i = 0;
        for(; i < text.size(); i++)
        {
            if(text[i] == ' ')
            {
                space++;
                if(~start)
                {
                    words.push_back(text.substr(start, i - start));
                    start = -1;
                }
            }
            else
                if(!(~start))
                    start = i;
        }
        if(text[i-1] != ' ')
            words.push_back(text.substr(start));
        int n = words.size() - 1;
        if(!n)
            return words[0].append(space, ' ');
        string ans = "";
        int perSpace = space/(n);
        int lastSpace = space%(n);
        for(int i = 0; i < n; i++)
        {
            ans.append(words[i]);
            ans.append(perSpace, ' ');
        }
        ans.append(words[n]);
        ans.append(lastSpace, ' ');
        return ans;
    }
};
// @lc code=end

