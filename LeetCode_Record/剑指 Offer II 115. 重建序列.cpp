#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        int n = nums.size();
        vector<int> inDegree(n+1);
        vector<unordered_set<int>> graph(n + 1);
        for(auto& i : sequences)
        {
            for(int j = 1; j < i.size();j++)
            {
                int prev = i[j - 1], next = i[j];
                if (!graph[prev].count(next)) {
                    graph[prev].emplace(next);
                    inDegree[next]++;
                }
            }
        }
    
        queue<int> qu;
        for(int i = 1; i <= n;i++)
        {
            if(inDegree[i] == 0)
            {
                qu.push(i);
            }
        }
        while(!qu.empty())
        {
            if(qu.size()>1)
            {
                return false;
            }
            int num = qu.front();
            qu.pop();
            for(auto& i : graph[num])
            {
                inDegree[i] --;
                if(inDegree[i] == 0)
                {
                    qu.push(i);
                }
            }
        }
        return true;
    }
};