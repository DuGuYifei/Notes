#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=1606 lang=cpp
 *
 * [1606] 找到处理最多请求的服务器
 */

// @lc code=start
class Solution
{
public:
    vector<int> busiestServers(int k, vector<int> &arrival, vector<int> &load)
    {
        int n = arrival.size();
        vector<int>handle(k,0);
        //vector<bool>freeServer(k,true);
        // 将用过一次的服务器等k差加下一循环，这样最前面的是比 mod k 大的，后面是比mod k 小的
        priority_queue<int, vector<int>, greater<int>> freeServer;
        // int,int : [第几秒结束] [第几个服务器]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> busyServer;

        for (int i = 0; i < k; i++)
        {
            freeServer.push(i);
        }

        // i 代表第几个请求
        for (int i = 0; i < n; i++)
        {
            // while (!busyServer.empty() && busyServer.top().first <= arrival[i])
            // {
            //     int id = busyServer.top().second;
            //     freeServer[id] = true;
            //     busyServer.pop();
            // }
            // int id = i%k;
            // for(int j = id,c = 0;;j++)
            // {
            //     if(j == k)
            //         j = 0;
            //     if(j==id)
            //     {
            //         c++;
            //         if(c==2)
            //             break;
            //     }
            //     if(freeServer[j])
            //     {
            //         freeServer[j] = false;
            //         busyServer.push(pair(arrival[i] + load[i], j));
            //         handle[j] ++ ;
            //         break;
            //     }
            // }
            while (!busyServer.empty() && busyServer.top().first <= arrival[i])
            {
                int id = busyServer.top().second;
                freeServer.push(i + ((id - i) % k + k) % k);
                busyServer.pop();
            }
            if(!freeServer.empty())
            {
                int id = freeServer.top()%k;
                freeServer.pop();
                handle[id]++;
                busyServer.push(pair(arrival[i]+load[i], id));
            }
        }
        vector<int>ans;
        for(int max=0,i=0;i<k;i++)
        {
            if(max<handle[i])
            {
                max = handle[i];
                ans = vector<int>{i};
            }
            else if(max==handle[i])
            {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
// @lc code=end
