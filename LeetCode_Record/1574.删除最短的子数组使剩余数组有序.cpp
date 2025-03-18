#include <vector>
#include <utility>
using namespace std;
/*
 * @lc app=leetcode.cn id=1574 lang=cpp
 *
 * [1574] 删除最短的子数组使剩余数组有序
 *
 * https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/description/
 *
 * algorithms
 * Medium (37.01%)
 * Likes:    171
 * Dislikes: 0
 * Total Accepted:    19.9K
 * Total Submissions: 47.8K
 * Testcase Example:  '[1,2,3,10,4,2,3,5]'
 *
 * 给你一个整数数组 arr ，请你删除一个子数组（可以为空），使得 arr 中剩下的元素是 非递减 的。
 * 
 * 一个子数组指的是原数组中连续的一个子序列。
 * 
 * 请你返回满足题目要求的最短子数组的长度。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：arr = [1,2,3,10,4,2,3,5]
 * 输出：3
 * 解释：我们需要删除的最短子数组是 [10,4,2] ，长度为 3 。剩余元素形成非递减数组 [1,2,3,3,5] 。
 * 另一个正确的解为删除子数组 [3,10,4] 。
 * 
 * 示例 2：
 * 
 * 
 * 输入：arr = [5,4,3,2,1]
 * 输出：4
 * 解释：由于数组是严格递减的，我们只能保留一个元素。所以我们需要删除长度为 4 的子数组，要么删除 [5,4,3,2]，要么删除 [4,3,2,1]。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：arr = [1,2,3]
 * 输出：0
 * 解释：数组已经是非递减的了，我们不需要删除任何元素。
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：arr = [1]
 * 输出：0
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 10^5
 * 0 <= arr[i] <= 10^9
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int left = -1, right = -1;
        int n = arr.size();
        for(int i = 1; i < n; i++){
            if(arr[i - 1] > arr[i]){
                left = i - 1;
                right = i;
                break;
            }
        }
        if(left == -1)
            return 0;
        for(int i = right + 1; i < n; i++){
            if(arr[i - 1] > arr[i])
                right = i;
        }
        int ans = min(right, n - left - 1);
        n--;
        int leftv = left, rightv = right;
        int pos = left;
        while(arr[left] > arr[right]){
            if(left){
                left--;
                leftv = left;
            }
            else{
                leftv = -1;
                if(right >= n) 
                    return min(ans, n);
            } 
            if(right < n){
                right++;       
                rightv = right;
            }else{
                rightv = n + 1;
            }
        }
        if(leftv == -1 || rightv == n + 1)
            return ans;
        int i = left;
        int j = right;
        while(arr[j - 1] <= arr[j] && arr[j - 1] >= arr[left])
            j--;
        while(arr[i + 1] >= arr[i] && arr[i + 1] <= arr[right])
            i++;
        return min(right - i - 1, j - left - 1);
    }
};
// @lc code=end

