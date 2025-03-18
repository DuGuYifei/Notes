#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=857 lang=cpp
 *
 * [857] 雇佣 K 名工人的最低成本
 */

// @lc code=start
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<int> idx(n);
        iota(idx.begin(),idx.end(),0);
        sort(idx.begin(), idx.end(), [w = wage.data(), q = quality.data()](const int& a, const int& b)->bool{
            return w[a] * q[b] <= w[b] * q[a];
        });
        
        int totalQ = 0;
        priority_queue<int> q;
        for(int i = 0; i < k; i++)
        {
            totalQ += quality[idx[i]];
            q.push(quality[idx[i]]);
        }
        double ans = (double)wage[idx[k-1]]/quality[idx[k-1]] * totalQ;

        for(int i = k; i < n; i++)
        {
            int temp = quality[idx[i]];
            totalQ -= q.top();
            totalQ += temp;
            ans = min(ans, (double)wage[idx[i]]/temp * totalQ);
            q.pop();
            q.push(temp);
        }
        return ans;
    }
};
// @lc code=end

