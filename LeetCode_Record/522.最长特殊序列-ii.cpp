#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=522 lang=cpp
 *
 * [522] 最长特殊序列 II
 */

// @lc code=start
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        int ans = -1;
        for(int i = 0;i<n;i++)
        {
            int j = 0;
            for(; j < n;j++)
            {
                if(j != i)
                {
                    if(isSubset(strs[i],strs[j]))
                    {
                        break;
                    }
                }
            }
            if(j == n)
            {
                ans = max(ans, (int)strs[i].size());
            }
        }
        return ans;
    }

    bool isSubset(const string& source, const string& target)
    {
        int s = 0;
        int t = 0;
        while(s!=source.size() && t != target.size())
        {
            if(source[s] == target[t])
            {
                s++;
            }
            t++;
        }
        return s == source.size();
    }
};
// @lc code=end

