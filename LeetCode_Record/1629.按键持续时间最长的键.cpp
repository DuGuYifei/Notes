#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1629 lang=cpp
 *
 * [1629] 按键持续时间最长的键
 */

// @lc code=start
class Solution {
public:
    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        char maxkey = keysPressed[0];
        int maxtime = releaseTimes[0];
        for(int i = 1;i<releaseTimes.size();i++)
        {
            int time = releaseTimes[i] - releaseTimes[i-1];
            if(time > maxtime || (time == maxtime && keysPressed[i]>maxkey))
            {
                maxkey = keysPressed[i];
                maxtime = time;
            }
        }
        return maxkey;
    }
};
// @lc code=end

