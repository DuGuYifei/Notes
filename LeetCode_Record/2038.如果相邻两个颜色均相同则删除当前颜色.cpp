#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=2038 lang=cpp
 *
 * [2038] 如果相邻两个颜色均相同则删除当前颜色
 */

// @lc code=start
class Solution {
public:
    bool winnerOfGame(string colors) {
        int n = colors.size();
        if(n < 3)
            return false;
        char prev = colors[0];
        char next = colors[2];
        char now = colors[1];
        int i = 2;
        int A = 0;
        int B = 0;
        while(i < n)
        {
            if(prev == now)
            {
                if(prev == next)
                {
                    if(prev == 'A')
                        A++;
                    else
                        B++;
                }
            }
            prev = now;
            now = next;
            if(++i<n)
                next = colors[i];
        }
        return A > B;
    }
};
// @lc code=end

