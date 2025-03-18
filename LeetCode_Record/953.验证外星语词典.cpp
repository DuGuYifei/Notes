#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=953 lang=cpp
 *
 * [953] 验证外星语词典
 */

// @lc code=start
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        int alph[26];
        for(int i = 0; i < 26;i++)
        {
            alph[order[i] - 'a'] = i;
        }
        int n1,n2 = words[0].size() - 1;
        for(int i = 1;i < words.size();i++)
        {
            n1 = n2;
            n2 = words[i].size() - 1;
            for(int j = 0;j <= n2;j++)
            {
                int t1 = alph[words[i-1][j]-'a'];
                int t2 = alph[words[i][j]-'a'];
                if(t1 > t2)
                    return false;
                if(t1 < t2)
                    break;
                if(j == n1)
                    break;
                if(j == n2)
                    return false;
            }
        }
        return true;
    }
};
// @lc code=end

