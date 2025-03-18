#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=717 lang=cpp
 *
 * [717] 1比特与2比特字符
 */

// @lc code=start
class Solution
{
public:
    bool isOneBitCharacter(vector<int> &bits)
    {
        // int i = 0;
        // int n = bits.size();
        // // for (; i < n - 1; i++)
        // // {
        // //     if (bits[i] == 1)
        // //     {
        // //         i++;
        // //     }
        // // }
        // while(i<n-1)
        // {
        //     i += bits[i]+1;
        // }
        // // if (i == n)
        // //     return false;
        // // if (bits[i] == 1)
        // //     return false;
        // // return true;
        // return i == n-1;

        int i = bits.size() - 1;
        int n1= 0;
        while(i>=0)
        {
            if(bits[i]==1)
            {
                n1++;
                i--;
            }
            else
            {
                break;
            }
        }
        return n1%2 - 1 ;
    }
};
// @lc code=end
