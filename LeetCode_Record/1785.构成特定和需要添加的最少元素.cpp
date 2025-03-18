#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1785 lang=cpp
 *
 * [1785] 构成特定和需要添加的最少元素
 *
 * https://leetcode-cn.com/problems/minimum-elements-to-add-to-form-a-given-sum/description/
 *
 * algorithms
 * Medium (35.70%)
 * Likes:    11
 * Dislikes: 0
 * Total Accepted:    9.5K
 * Total Submissions: 24.5K
 * Testcase Example:  '[1,-1,1]\n3\n-4'
 *
 * 给你一个整数数组 nums ，和两个整数 limit 与 goal 。数组 nums 有一条重要属性：abs(nums[i])  。
 * 
 * 返回使数组元素总和等于 goal 所需要向数组中添加的 最少元素数量 ，添加元素 不应改变 数组中 abs(nums[i])  这一属性。
 * 
 * 注意，如果 x >= 0 ，那么 abs(x) 等于 x ；否则，等于 -x 。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [1,-1,1], limit = 3, goal = -4
 * 输出：2
 * 解释：可以将 -2 和 -3 添加到数组中，数组的元素总和变为 1 - 1 + 1 - 2 - 3 = -4 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,-10,9,1], limit = 100, goal = 0
 * 输出：1
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 1 
 * -limit 
 * -10^9 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        long long sum = -goal;
        for(auto& i:nums){
            sum += i;
        }
        return (abs(sum) + limit - 1) / limit;
    }
};
// @lc code=end

