#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=811 lang=cpp
 *
 * [811] 子域名访问计数
 */

// @lc code=start
class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> res;
        for(auto& i : cpdomains)
        {
            string num = "";
            int j = 0;
            while(i[j] != ' ')
                num.push_back(i[j++]);
            int numInt = stoi(num);
            
            j++;
            
            res[i.substr(j)] += numInt;
            int n = i.size();
            while( j < n )
            {
                if(i[j++] == '.')
                {
                    res[i.substr(j)] += numInt;
                }
            }
        }
        vector<string> ans;
        for(auto&& [domain, cnt] : res)
        {
            ans.push_back(to_string(cnt) + ' ' + domain);
        }
        return ans;
    }
};
// @lc code=end

