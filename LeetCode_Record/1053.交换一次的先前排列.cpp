#include <vector>
#include <set>
#include <utility>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=1053 lang=cpp
 *
 * [1053] 交换一次的先前排列
 *
 * https://leetcode.cn/problems/previous-permutation-with-one-swap/description/
 *
 * algorithms
 * Medium (45.99%)
 * Likes:    130
 * Dislikes: 0
 * Total Accepted:    26.6K
 * Total Submissions: 54.8K
 * Testcase Example:  '[3,2,1]'
 *
 * 给你一个正整数数组 arr（可能存在重复的元素），请你返回可在 一次交换（交换两数字 arr[i] 和 arr[j] 的位置）后得到的、按字典序排列小于
 * arr 的最大排列。
 * 
 * 如果无法这么操作，就请返回原数组。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：arr = [3,2,1]
 * 输出：[3,1,2]
 * 解释：交换 2 和 1
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：arr = [1,1,5]
 * 输出：[1,1,5]
 * 解释：已经是最小排列
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：arr = [1,9,4,6,7]
 * 输出：[1,7,4,6,9]
 * 解释：交换 9 和 7
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 10^4
 * 1 <= arr[i] <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        // int n = arr.size();
        // set<pair<int,int>> numId;
        // numId.emplace(arr[n - 1], 1);
        // for(int i = n - 2; i >= 0; i--){
        //     if(arr[i] > numId.begin()->first){
        //         int id = n - prev(numId.lower_bound({arr[i], -1}))->second;
        //         swap(arr[i], arr[id]);
        //         break;
        //     }
        //     numId.emplace(arr[i], n - i);
        // }
        // return arr;
        int n = arr.size();
        int mini = arr.back();
        for(int i = n - 2; i >= 0; i--){
            if(arr[i] > mini){
                int id = i + 1;
                for(int j = i + 1; j < n; j++){
                    if(arr[j] < arr[i] && arr[j] > arr[id]){
                        id = j;
                    }
                }
                swap(arr[i], arr[id]);
                break;
            }
            mini = min(mini, arr[i]);
        }
        return arr;
    }
};
// @lc code=end

