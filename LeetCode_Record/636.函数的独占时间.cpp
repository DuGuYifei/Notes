#include <vector>
#include <stack>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=636 lang=cpp
 *
 * [636] 函数的独占时间
 */

// @lc code=start
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        stack<pair<int, int>> run;
        vector<int> ans(n);
        for(auto& i : logs)
        {
            int idx, timestamp;
            char type[6];
            sscanf(i.c_str(), "%d:%[^:]:%d", &idx, type, &timestamp);
            if(type[0] == 's')
            {
                if(!run.empty())
                {
                    auto& t = run.top();
                    ans[t.first] += timestamp - t.second; // start时间戳的开头
                }
                run.emplace(idx, timestamp);
            }
            else
            {
                auto& t = run.top();
                run.pop();
                ans[t.first] += timestamp - t.second + 1; // end时间戳的末尾
                if(!run.empty())
                {
                    run.top().second = timestamp + 1;
                }
            }
        }
        return ans;
    }
};
// @lc code=end

