/*
 * @lc app=leetcode.cn id=744 lang=cpp
 *
 * [744] 寻找比目标字母大的最小字母
 */

// @lc code=start
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        // for(char& i : letters)
        // {
        //     if(i > target)
        //     {
        //         return i;
        //     }
        // }
        //return letters[0];

        return target > letters.back()? letters[0]:*upper_bound(letters.begin(),letters.end(),target);
    }
};
// @lc code=end

