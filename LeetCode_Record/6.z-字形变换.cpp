#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=6 lang=cpp
 *
 * [6] Z 字形变换
 */

// @lc code=start
class Solution
{
public:
    string convert(string s, int numRows)
    {
        if (numRows == 1) return s;
        
        int currentRow = 1;
        int sizeS = s.size();

        string s2;
        int groupMems = (numRows - 1) * 2;

        int index = 0;

        while(index<sizeS)
        {
            s2.append(1,s[index]);
            index += groupMems;
        }
        
        for(int i = 1;i < numRows-1;i++)
        {
            index = i;
            int add = groupMems - i * 2;
            while(index<sizeS)
            {
                s2.append(1,s[index]);
                index += add;
                add = groupMems - add;//***********************key*************************
            }
        }

        index = numRows - 1;
        while(index<sizeS)
        {
            
            s2.append(1,s[index]);
            index += groupMems;
        }

        return s2;
    }
};
// @lc code=end
