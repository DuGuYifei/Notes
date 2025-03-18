#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=698 lang=cpp
 *
 * [698] 划分为k个相等的子集
 */

// @lc code=start
class Solution {
private:
    int n;
    vector<int> subsets;
    int k;
    int avg;
public:
    bool dfs(vector<int>& nums, int i){
        // 设置动态规划的终止态
        if(i == n)
            return true;
        // 思想是将这个数放进每一个子集里试试
        for(int j = 0; j < k; j++)
        {
            // 意思就是这种情况跟刚才一模一样没必要再做一遍
            if (j && subsets[j] == subsets[j - 1]) {
                continue;
            }
            subsets[j] += nums[i];
            if(subsets[j] <= avg && dfs(nums, i+1))
                return true;
            subsets[j] -= nums[i];
        }
        return false;
    }

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k)
            return false;
        avg = sum/k;
        subsets = vector<int>(k, 0);
        this->k = k;
        // 排序剪枝的解释：最大的数一定有个集合可以放，一个集合已经有最大的了，那么剩下能放的数字就有限制
        sort(nums.begin(), nums.end(), greater<int>());
        n = nums.size();
        return dfs(nums, 0);
    }
};
// @lc code=end

