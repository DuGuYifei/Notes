#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1601 lang=cpp
 *
 * [1601] 最多可达成的换楼请求数目
 */

// @lc code=start
class Solution
{
    int zeroBuildings;
    int fullRequests = 0;
    int ans = 0;
    int size;
    vector<int> change;

public:
    int maximumRequests(int n, vector<vector<int>> &requests)
    {
        change.resize(n);
        zeroBuildings = n;
        size = requests.size();
        backTrack(n,requests,0);
        return ans;
    }
    void backTrack(int n, vector<vector<int>> &requests, int nthRequests)
    {
        if (nthRequests == size)
        {
            if (zeroBuildings == n)
                ans = max(ans, fullRequests);
            return;
        }

        backTrack(n,requests,nthRequests+1);

        int z = zeroBuildings;//used for recover
        int x = requests[nthRequests][0];
        int y = requests[nthRequests][1];
        zeroBuildings -= change[x]==0;
        zeroBuildings -= change[y]==0;
        change[x]--;
        change[y]++;
        zeroBuildings += change[x]==0;
        zeroBuildings += change[y]==0;
        fullRequests++;

        backTrack(n,requests,nthRequests+1);

        change[x]++;
        change[y]--;
        fullRequests --;
        zeroBuildings = z;
    }
};
// @lc code=end
