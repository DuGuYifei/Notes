#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1235 lang=cpp
 *
 * [1235] 规划兼职工作
 *
 * https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/description/
 *
 * algorithms
 * Hard (47.44%)
 * Likes:    199
 * Dislikes: 0
 * Total Accepted:    12.7K
 * Total Submissions: 25.4K
 * Testcase Example:  '[1,2,3,3]\n[3,4,5,6]\n[50,10,40,70]'
 *
 * 你打算利用空闲时间来做兼职工作赚些零花钱。
 * 
 * 这里有 n 份兼职工作，每份工作预计从 startTime[i] 开始到 endTime[i] 结束，报酬为 profit[i]。
 * 
 * 给你一份兼职工作表，包含开始时间 startTime，结束时间 endTime 和预计报酬 profit 三个数组，请你计算并返回可以获得的最大报酬。
 * 
 * 注意，时间上出现重叠的 2 份工作不能同时进行。
 * 
 * 如果你选择的工作在时间 X 结束，那么你可以立刻进行在时间 X 开始的下一份工作。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
 * 输出：120
 * 解释：
 * 我们选出第 1 份和第 4 份工作， 
 * 时间范围是 [1-3]+[3-6]，共获得报酬 120 = 50 + 70。
 * 
 * 
 * 示例 2：
 * 
 * ⁠
 * 
 * 输入：startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit =
 * [20,20,100,70,60]
 * 输出：150
 * 解释：
 * 我们选择第 1，4，5 份工作。 
 * 共获得报酬 150 = 20 + 70 + 60。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 
 * 输入：startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 * 1 <= startTime[i] < endTime[i] <= 10^9
 * 1 <= profit[i] <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    //dp[i]=max(dp[i−1],dp[k]+profit[i−1])
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs(n);
        for(int i = 0; i < n; i++)
            jobs[i] = {startTime[i], endTime[i], profit[i]};
        sort(jobs.begin(), jobs.end(), [](const vector<int>& job1, const vector<int>& job2){
            return job1[1] < job2[1];
        });
        vector <int> dp(n + 1);
        for(int i = 1; i <= n; i++)
        {
            int k = upper_bound(jobs.begin(), jobs.begin() + i - 1, jobs[i-1][0], [&](int st, const vector<int>& job){
                return st < job[1]; // 找到第一个比它大的值的索引，则前一个刚好是最后一个小于等于 jobs[i-1][0]的值
            }) - jobs.begin();
            dp[i] = max(dp[i - 1], dp[k] + jobs[i - 1][2]); // 直接用k是因为dp有个默认dp[0] = 0，相当于比jobs多出一个索引
        }
        return dp[n];
    }
};
// @lc code=end

