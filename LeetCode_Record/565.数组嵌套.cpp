/*
 * @lc app=leetcode.cn id=565 lang=cpp
 *
 * [565] 数组嵌套
 */

// @lc code=start
class Solution {
public:
    // 关键点在于这是个有向图的环，一个或多个换，不用按顺序挨个走，也能遍历所有的
    int arrayNesting(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 0;i < n; i++)
        {
            int cnt = 0;
            while(numms[i] != n)
            {
                int num = nums[i];
                cnt++;
                nums[i] = n;
                i = num;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};
// @lc code=end

