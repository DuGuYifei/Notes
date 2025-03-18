#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=2000 lang=cpp
 *
 * [2000] 反转单词前缀
 */

// @lc code=start
class Solution {
public:
    string reversePrefix(string word, char ch) {
        int index = 0;
        int n = word.size();
        while(word[index]!=ch && index < n)
        {
            index++;
        }
        if(word[index] == ch)
        {
            int rightMid = (index+1) >> 1;
            int left = 0;
            while(index!=rightMid-1)
            {
                char temp = word[index];
                word[index] = word[left];
                word[left] = temp;
                index--;
                left++;
            }
        }
        return word;
    }
};
// @lc code=end

