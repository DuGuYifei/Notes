#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    //Exceed time limit
    //int n;
    // int minCost(vector<vector<int>>& costs) {
    //     n = costs.size();
    //     return min({costs[0][0] + dfs(1,0,costs),
    //     costs[0][1] + dfs(1,1,costs),
    //     costs[0][2] + dfs(1,2,costs)});
    // }

    // int dfs(int nth, int prevCol, vector<vector<int>>& costs)
    // {
    //     if(nth == n)
    //         return 0;
    //     int col1 = (prevCol + 1)%3;
    //     int col2 = (prevCol + 2)%3;
    //     return min(costs[nth][col1] + dfs(nth + 1, col1, costs), 
    //     costs[nth][col2] + dfs(nth + 1, col2, costs));
    // }

    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        vector<int> dp = costs[0];
        for(int i = 1; i <n;i++)
        {
            vector<int> newdp(3);
            for(int j = 0; j < 3 ; j ++)
            {
                newdp[j] = min(dp[(j+1)%3], dp[(j+2)%3]) + costs[i][j];
            }
            dp = newdp;
        }        
        return *min_element(dp.begin(),dp.end()); 
    }
};