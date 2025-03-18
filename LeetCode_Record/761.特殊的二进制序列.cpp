#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=761 lang=cpp
 *
 * [761] 特殊的二进制序列
 */

// @lc code=start
class Solution {
public:
    string makeLargestSpecial(string s) {
        if (s.size() <= 2) {
            return s;
        }

        int cnt = 0, left = 0;
        vector<string> subs;
        for(int i = 0; i < s.size();i++)
        {
            if(s[i] == '1')
            {
                cnt++;
            }
            else
            {
                cnt--;
                if(cnt == 0)
                {
                    // 因为开头的1 和 结尾的0 不能换位置，所以要left + 1
                    subs.push_back("1" + makeLargestSpecial(s.substr(left + 1, i - left - 1)) + "0");
                    left = i + 1; // 因为最后0结尾后一定是1
                }
            }
        }

        // 开始处理已经处理好内部的部分
        sort(subs.begin(), subs.end(), greater<string>{});
        string ans = accumulate(subs.begin(), subs.end(), ""s);
        return ans;
    }
};
// @lc code=end

