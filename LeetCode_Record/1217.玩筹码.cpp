/*
 * @lc app=leetcode.cn id=1217 lang=cpp
 *
 * [1217] 玩筹码
 */

// @lc code=start
class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        int odd = 0, even = 0;
        for(int& i : position)
        {
            if(i%2)
                even++;
            else
                odd++;
        }
        return min(even, odd);
    }
};
// @lc code=end

