/*
 * @lc app=leetcode.cn id=1450 lang=cpp
 *
 * [1450] 在既定时间做作业的学生人数
 */

// @lc code=start
class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int ans = 0;
        for(int i = 0; i < startTime.size();i++)
        {
            if(startTime[i] <= queryTime && endTime[i] >= queryTime)
            {
                ans++;
            }
        }
        return ans;
    }
};
// @lc code=end

