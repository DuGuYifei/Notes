#include <string>
using namespace std;
/*
# * @lc app=leetcode.cn id=2047 lang=cpp
 *
 * [2047] 句子中的有效单词数
 */

// @lc code=start
class Solution
{
public:
    int countValidWords(string sentence)
    {
        int n = 0;
        for (int i = 0; i < sentence.size(); i++)
        {
            if (sentence[i] == ' ')
                continue;
            bool haveAlphabet = false;
            bool haveHyphen = false;
            bool pass = false;
            while (sentence[i] != ' ' && sentence[i] != '\0')
            {
                if (sentence[i] >= 97 && sentence[i] <= 122)
                {
                    haveAlphabet = true;
                }

                else if (sentence[i] == '-')
                {
                    if (haveAlphabet && !haveHyphen)
                    {
                        haveAlphabet = false;
                    }
                    else
                    {
                        haveAlphabet = false;
                        while (sentence[i] != ' ' && sentence[i] != '\0')
                            i++;
                        break;
                    }
                    haveHyphen = true;
                }
                else
                {
                    if ((sentence[i] >= 48 && sentence[i] <= 97)||sentence[i + 1] != ' ' && sentence[i + 1] != '\0')
                    {
                        haveAlphabet = false;
                        while (sentence[i] != ' '&&sentence[i]!='\0')
                            i++;
                        break;
                    }
                    if(haveHyphen && !haveAlphabet)
                    {
                        i++;
                        break;
                    }
                    pass = true;
                }
                i++;
            }
            if (haveAlphabet||pass)
                n++;
        }
        return n;
    }
};
// @lc code=end
