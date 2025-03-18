#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=821 lang=cpp
 *
 * [821] 字符的最短距离
 */

// @lc code=start
class Solution
{
public:
    vector<int> shortestToChar(string s, char c)
    {
        int n = s.size();
        vector<int> ans(n);

        //方法1，2
        // vector<int> cindex;
        // for (int i = 0; i < n; i++)
        // {
        //     if (s[i] == c)
        //     {
        //         cindex.push_back(i);
        //     }
        // }

        //方法1
        // int ci_l = 0, ci_r = 0;
        // for(int i = 0;i < n; i++)
        // {
        //     if(i == cindex[ci_r])
        //     {
        //         ci_l = ci_r;
        //         if(ci_r<cindex.size()-1)
        //             ci_r++;
        //         ans[i] = 0;
        //         continue;
        //     }
        //     if(i<=(cindex[ci_l]+cindex[ci_r])/2)
        //     {
        //         ans[i] = abs(i - cindex[ci_l]);
        //     }
        //     else
        //         ans[i] = abs(cindex[ci_r] - i);
        // }

        //方法2
        // int right = cindex[0];
        // int ci_r = 0;
        // int left = right;
        // int half = (left+right)/2;
        // for(int i = 0;i<n;i++)
        // {
        //     if(i == right)
        //     {
        //         ans[i] = 0;
        //         left = right;
        //         if(++ci_r < cindex.size())
        //             right = cindex[ci_r];
        //         half = (left+right)/2;
        //         continue;
        //     }
        //     if(i <= half)
        //         ans[i] = abs(i - left);
        //     else
        //         ans[i] = abs(right - i);
        // }

        //方法3
        // 先从左到右，获得距离左边c最近的距离，第一个c之前是整个长度
        for (int i = 0, idx = -n; i < n; ++i)
        {
            if (s[i] == c)
            {
                idx = i;
            }
            ans[i] = i - idx;
        }
        // 再从右到左，获得距离右边c最近的距离，第一个c之前是整个长度
        // 此次遍历用min()获得较小的那个距离（左/右）
        for (int i = n - 1, idx = 2 * n; i >= 0; --i)
        {
            if (s[i] == c)
            {
                idx = i;
            }
            ans[i] = min(ans[i], idx - i);
        }

        return ans;
    }
};
// @lc code=end
