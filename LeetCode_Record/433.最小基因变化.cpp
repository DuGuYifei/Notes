#include <unordered_set>
#include <string>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=433 lang=cpp
 *
 * [433] 最小基因变化
 */

// @lc code=start
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        if(start == end)
            return 0;
        // if(find(bank.begin(),bank.end(),end) == bank.end())
        //     return -1;
        
        unordered_set<string> cnt;
        unordered_set<string> visited;
        char keys[4] = {'A', 'C', 'G', 'T'};        
        for (auto & w : bank) {
            cnt.emplace(w);
        }

        if (!cnt.count(end)) {
            return -1;
        }
        int step = 0;
        queue<string> wait;
        wait.push(start);
        visited.emplace(start);
        while(!wait.empty())
        {
            int n = wait.size();
            for(int i = 0;i<n;i++)
            {
                string cur = wait.front();
                wait.pop();
                for(int j = 0;j<8;j++)
                {
                    for(int k = 0;k<4;k++)
                    {
                        if(keys[k] == cur[j])
                            continue;
                        string temp = cur;
                        temp[j] = keys[k];
                        if(temp == end)
                                return step+1;
                        if(!visited.count(temp) && cnt.count(temp))
                        {
                            wait.emplace(temp);
                            visited.emplace(temp);
                        }
                    }
                }
            }
            step++;
        }
        return -1;
    }
};
// @lc code=end

