#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] 回文数
 */

// @lc code=start
class Solution
{
public:
    bool isPalindrome(int x)
    {
        // string s = to_string(x);
        // int left, right, len = s.length();
        // if(len%2==0)
        // {
        //     left = len/2-1;
        //     right = left+1;
        // }
        // else
        // {
        //     left = len/2;
        //     right = left;
        // }
        // int is_p = true;
        // while(left>=0)
        // {
        //     if(s[left]!=s[right])
        //         is_p = false;
        //     left--;
        //     right++;
        // }
        // return is_p;
        
        
        // if (x < 0 || (x % 10 == 0 && x != 0))
        //     return false;
        // unsigned int origin = x;
        // unsigned int pop, result = 0;
        // while(x!=0)
        // {
        //     pop = x%10;
        //     x /= 10;

        //     result = result * 10 + pop;

        // }

        // return result == origin;

        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;
        int result = 0;
        while (x > result)
        {
            result = result * 10 + x % 10;
            x /= 10;
        }
        return x == result || x == result / 10;
    }
};
// @lc code=end
