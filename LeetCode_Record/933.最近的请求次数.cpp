#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=933 lang=cpp
 *
 * [933] 最近的请求次数
 */

// @lc code=start
class RecentCounter {
    //vector<int> history;
    queue<int> history;
public:
    RecentCounter() {
        //history = queue<int>();
    }
    
    int ping(int t) {
        history.push(t);
        int start = t - 3000;
        while(history.front()<start)
        {
            history.pop();
        }
        return history.size();

        // int start = t - 3000;
        // int ans = 1;
        // for(int i = history.size() - 1;;i--)
        // {
        //     if(i==-1)
        //         break;
        //     if(history[i]>=start)
        //         ans++;
        // }
        // history.push_back(t);
        // return ans;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
// @lc code=end

