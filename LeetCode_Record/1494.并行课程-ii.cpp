#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1494 lang=cpp
 *
 * [1494] 并行课程 II
 *
 * https://leetcode.cn/problems/parallel-courses-ii/description/
 *
 * algorithms
 * Hard (40.54%)
 * Likes:    114
 * Dislikes: 0
 * Total Accepted:    5K
 * Total Submissions: 11.9K
 * Testcase Example:  '4\n[[2,1],[3,1],[1,4]]\n2'
 *
 * 给你一个整数 n 表示某所大学里课程的数目，编号为 1 到 n ，数组 relations 中， relations[i] = [xi, yi]
 * 表示一个先修课的关系，也就是课程 xi 必须在课程 yi 之前上。同时你还有一个整数 k 。
 * 
 * 在一个学期中，你 最多 可以同时上 k 门课，前提是这些课的先修课在之前的学期里已经上过了。
 * 
 * 请你返回上完所有课最少需要多少个学期。题目保证一定存在一种上完所有课的方式。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
 * 输出：3 
 * 解释：上图展示了题目输入的图。在第一个学期中，我们可以上课程 2 和课程 3 。然后第二个学期上课程 1 ，第三个学期上课程 4 。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：n = 5, relations = [[2,1],[3,1],[4,1],[1,5]], k = 2
 * 输出：4 
 * 解释：上图展示了题目输入的图。一个最优方案是：第一学期上课程 2 和 3，第二学期上课程 4 ，第三学期上课程 1 ，第四学期上课程 5 。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 11, relations = [], k = 2
 * 输出：6
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 15
 * 1 <= k <= n
 * 0 <= relations.length <= n * (n-1) / 2
 * relations[i].length == 2
 * 1 <= xi, yi <= n
 * xi != yi
 * 所有先修关系都是不同的，也就是说 relations[i] != relations[j] 。
 * 题目输入的图是个有向无环图。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> dp(1 << n, INT_MAX);
        vector<int> need(1 << n, 0);
        for (auto& edge : relations) {
            need[(1 << (edge[1] - 1))] |= 1 << (edge[0] - 1);
        }
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) {
            need[i] = need[i & (i - 1)] | need[i & (-i)];
            if ((need[i] | i) != i) { // i 中有任意一门课程的前置课程没有完成学习
                continue;
            }
            int valid = i ^ need[i]; // 当前学期可以进行学习的课程集合
            if (__builtin_popcount(valid) <= k) { // 如果个数小于 k，则可以全部学习，不再枚举子集
                dp[i] = min(dp[i], dp[i ^ valid] + 1);
            } else { // 否则枚举当前学期需要进行学习的课程集合
                for (int sub = valid; sub; sub = (sub - 1) & valid) {
                    if (__builtin_popcount(sub) <= k) {
                        dp[i] = min(dp[i], dp[i ^ sub] + 1);
                    }
                }
            }
        }
        return dp[(1 << n) - 1];
    }
};

// @lc code=end

