#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=915 lang=cpp
 *
 * [915] 分割数组
 *
 * https://leetcode-cn.com/problems/partition-array-into-disjoint-intervals/description/
 *
 * algorithms
 * Medium (46.81%)
 * Likes:    213
 * Dislikes: 0
 * Total Accepted:    41.6K
 * Total Submissions: 83.3K
 * Testcase Example:  '[5,0,3,8,6]'
 *
 * 给定一个数组 nums ，将其划分为两个连续子数组 left 和 right， 使得：
 * 
 * 
 * left 中的每个元素都小于或等于 right 中的每个元素。
 * left 和 right 都是非空的。
 * left 的长度要尽可能小。
 * 
 * 
 * 在完成这样的分组后返回 left 的 长度 。
 * 
 * 用例可以保证存在这样的划分方法。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：nums = [5,0,3,8,6]
 * 输出：3
 * 解释：left = [5,0,3]，right = [8,6]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：nums = [1,1,1,0,6,12]
 * 输出：4
 * 解释：left = [1,1,1,0]，right = [6,12]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 2 <= nums.length <= 10^5
 * 0 <= nums[i] <= 10^6
 * 可以保证至少有一种方法能够按题目所描述的那样对 nums 进行划分。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size();
        vector<int> minRight(n, nums[n-1]);
        for(int i = n-2; i >= 0; i--)
        {
            if(nums[i] < minRight[i + 1])
                minRight[i] = nums[i];
            else
                minRight[i] = minRight[i + 1];
        }
        int maxLeft = 0;
        for(int i = 0; i < n; i++)
        {
            if(nums[i] > maxLeft)
                maxLeft = nums[i];
            if(maxLeft <= minRight[i+1])
                return i + 1;
        }
        return n;
    }
};
// @lc code=end

