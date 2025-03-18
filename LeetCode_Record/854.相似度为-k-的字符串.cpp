#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=854 lang=cpp
 *
 * [854] 相似度为 K 的字符串
 */

// @lc code=start
class Solution{
public:
    int minSwap(const string &s1, const string &s2, const int &pos){
        int tot = 0;
        for (int i = pos; i < s1.size(); i++)
        {
            tot += s1[i] != s2[i];
        }
        return tot + 1 >> 1;
    }

    int kSimilarity(string s1, string s2){
        string str1, str2;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) {
                str1.push_back(s1[i]);
                str2.push_back(s2[i]);
            }
        }
        int n = str1.size();
        if (n == 0) {
            return 0;
        }
        int ans = n - 1;
        function<void(int,int)> dfs = [&](int pos, int cost){
            if(cost > ans)
                return;
            while(pos < n && str1[pos] == str2[pos])
                pos++;
            if(pos == n){
                ans = min(ans, cost);
                return;
            }
            if(cost + minSwap(str1, str2, pos) >= ans)
                return;
            
            for(int i = pos + 1; i < n ; i++)
            {
                if(str1[i] == str2[pos])
                {
                    swap(str1[i], str1[pos]);
                    dfs(pos + 1, cost +1);
                    swap(str1[i], str1[pos]);
                }
            }
        };
        dfs(0,0);
        return ans;
    }
};
// @lc code=end
