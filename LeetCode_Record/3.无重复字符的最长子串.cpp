#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        // unordered_set<char> window;
        // int n = s.size();
        // int rk = 0, ans = 0; //右指针
        // for (int i = 0; i < n; i++) //左指针
        // {
        //     if (i != 0)
        //     {
        //         window.erase(s[i - 1]);
        //     }
        //     while (rk < n && !window.count(s[rk]))
        //     {
        //         window.insert(s[rk]);
        //         rk++;
        //     }
        //     ans = max(ans, rk - i);
        // }
        // return ans;

        bool hash[128] = {false}; //一共就只有128位ascii码
        int right = 0, left = 0, n = s.size(), ans = 0;
        for (; s[right] != '\0'; right++)
        {
            if(!hash[s[right]])
            {
                hash[s[right]] = true;
            }
            else
            {
                ans = max(ans, right - left);
                while(s[left]!=s[right])
                {
                    hash[s[left]] = false;
                    left++;
                }
                left++;
            }
        }
        ans = max(ans, right - left);
        return ans;

        // unordered_set<char> window;
        // int lk = 0, rk = 0, ans = 0; //右指针
        // for (; rk < s.size(); rk++)  //左指针
        // {
        //     if (window.find(s[rk]) == window.end())
        //     {
        //         window.insert(s[rk]);
        //     }
        //     else
        //     {
        //         ans = max(ans, rk - lk);
        //         while (s[lk]!=s[rk])
        //         {
        //             window.erase(s[lk]);
        //             lk++;
        //         }
        //         lk++;
        //     }
        // }
        // ans = max(ans,rk-lk);
        // return ans;
    }
};
// @lc code=end
