/*
 * @lc app=leetcode.cn id=806 lang=cpp
 *
 * [806] 写字符串需要的行数
 */

// @lc code=start
class Solution {
public:
    vector<int> numberOfLines(vector<int>& widths, string s) {
        int len = 0;
        int row = 1;
        for(char& i : s)
        {
            len += widths[i - 'a'];
            if(len > 100)
            {
                row++;
                len = widths[i - 'a'];
            }
        }
        return vector<int>{row, len};
    }
};
// @lc code=end

