/*
 * @lc app=leetcode.cn id=1455 lang=cpp
 *
 * [1455] 检查单词是否为句中其他单词的前缀
 */

// @lc code=start
class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int n = sentence.size();
        int m = searchWord.size();
        int j = 0;
        int ans = 1;
        for(int i = 0; i < n; i++)
        {       
            if(sentence[i] == searchWord[j])
            {
                j++;
                if(j==m)
                    return ans;
                else if(sentence[i+1] == ' ')
                {
                    j = 0;
                    i++;
                    ans++;
                }
                continue;
            }
            i++;
            while(i < n && sentence[i] != ' ')
            {
                i++;
            }
            j = 0;
            ans++;
        }
        return -1;
    }
};
// @lc code=end

