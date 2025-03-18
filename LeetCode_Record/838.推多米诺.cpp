#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=838 lang=cpp
 *
 * [838] 推多米诺
 */

// @lc code=start
class Solution
{
public:
    string pushDominoes(string dominoes)
    {
        int firstR = -1;
        bool isR = false;
        for (int i = 0; i < dominoes.size(); i++)
        {
            if (dominoes[i] == 'R')
            {
                firstR = i;
                isR = true;
                continue;
            }
            else if (dominoes[i] == 'L')
            {
                isR = false;
                int j = i - 1;
                for (; j > (firstR == -1 ? -1 : (firstR + i) >> 1); j--)
                {
                    if(dominoes[j] == 'L')
                        break;
                    dominoes[j] = 'L';
                }
                if (firstR != -1 && (firstR + i) % 2 == 0)
                {
                    dominoes[j] = '.';
                }
                firstR = -1;
                continue;
            }
            if (isR)
            {
                dominoes[i] = 'R';
            }
        }
        return dominoes;
    }
};
// @lc code=end
