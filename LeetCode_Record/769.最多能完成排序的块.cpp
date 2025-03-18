#include <vector>
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=769 lang=cpp
 *
 * [769] 最多能完成排序的块
 */

// @lc code=start
class Solution {
public:
    //key: [a0 ... ai ... an-1] 
    // a0 .. ai 的最大值应为 ai
    // 维护遇到的最大值，直到遇到i = max, 
    //因为已经确定顺序为 i = ai，跟768题不同，768不能确定每个chuk的最大最小值
    int maxChunksToSorted(vector<int>& arr) {
        int ans = 0, mx = 0;
        int n = arr.size();
        for(int i = 0;i < n; i++)
        {
            mx = max(mx, arr[i]);
            if(i == mx)
                ans++;
        }
        return ans;
    }
};
// @lc code=end

