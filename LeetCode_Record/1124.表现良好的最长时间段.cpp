#include <vector>
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=1124 lang=cpp
 *
 * [1124] 表现良好的最长时间段
 *
 * https://leetcode-cn.com/problems/longest-well-performing-interval/description/
 *
 * algorithms
 * Medium (32.92%)
 * Likes:    441
 * Dislikes: 0
 * Total Accepted:    38.5K
 * Total Submissions: 99.2K
 * Testcase Example:  '[9,9,6,0,6,6,9]'
 *
 * 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。
 * 
 * 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。
 * 
 * 所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。
 * 
 * 请你返回「表现良好时间段」的最大长度。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：hours = [9,9,6,0,6,6,9]
 * 输出：3
 * 解释：最长的表现良好时间段是 [9,9,6]。
 * 
 * 示例 2：
 * 
 * 
 * 输入：hours = [6,6,6]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= hours.length <= 10^4
 * 0 <= hours[i] <= 16
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> prefix(n + 1);
        stack<int> mono;
        mono.emplace(0);
        int sum = 0;
        for(int i = 1; i <= n; i++){
            if(hours[i - 1] > 8)
                sum++;
            else
                sum--;
            prefix[i] = sum;
            if(sum < prefix[mono.top()])
                mono.emplace(i);
        }

        int ans = 0;
        for(int i = n; i > 0; i--)
        {
            while(prefix[i] > prefix[mono.top()])
            {
                ans = max(ans, i - mono.top());
                mono.pop();
                if(mono.empty())
                    return ans;
            }
        }
        return ans;

        // int n = hours.size();
        // int goodCnt = 0;
        // for(int& i : hours)
        //     if(i > 8)
        //         goodCnt++;
        // return dfs(goodCnt, 0, n - 1, hours);
    }
    // int dfs(int goodCnt, int left, int right, vector<int>& hours){
    //     if(goodCnt == 0)
    //         return 0;
    //     int len = right - left + 1;
    //     while(goodCnt <= len / 2){
    //         if(hours[left] <= 8)
    //         {
    //             len--;
    //             left++;
    //         }
    //         else if(hours[right] <= 8)
    //         {
    //             len--;
    //             right--;
    //         }
    //         else
    //             return max(dfs(goodCnt - 1, left + 1, right, hours), dfs(goodCnt - 1, left, right - 1, hours));
    //     }
    //     return len;
    // }
};
// @lc code=end

