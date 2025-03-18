#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1000 lang=cpp
 *
 * [1000] 合并石头的最低成本
 *
 * https://leetcode.cn/problems/minimum-cost-to-merge-stones/description/
 *
 * algorithms
 * Hard (44.87%)
 * Likes:    329
 * Dislikes: 0
 * Total Accepted:    16.8K
 * Total Submissions: 31.7K
 * Testcase Example:  '[3,2,4,1]\n2'
 *
 * 有 N 堆石头排成一排，第 i 堆中有 stones[i] 块石头。
 *
 * 每次移动（move）需要将连续的 K 堆石头合并为一堆，而这个移动的成本为这 K 堆石头的总数。
 *
 * 找出把所有石头合并成一堆的最低成本。如果不可能，返回 -1 。
 *
 *
 *
 * 示例 1：
 *
 * 输入：stones = [3,2,4,1], K = 2
 * 输出：20
 * 解释：
 * 从 [3, 2, 4, 1] 开始。
 * 合并 [3, 2]，成本为 5，剩下 [5, 4, 1]。
 * 合并 [4, 1]，成本为 5，剩下 [5, 5]。
 * 合并 [5, 5]，成本为 10，剩下 [10]。
 * 总成本 20，这是可能的最小值。
 *
 *
 * 示例 2：
 *
 * 输入：stones = [3,2,4,1], K = 3
 * 输出：-1
 * 解释：任何合并操作后，都会剩下 2 堆，我们无法再进行合并。所以这项任务是不可能完成的。.
 *
 *
 * 示例 3：
 *
 * 输入：stones = [3,5,1,2,6], K = 3
 * 输出：25
 * 解释：
 * 从 [3, 5, 1, 2, 6] 开始。
 * 合并 [5, 1, 2]，成本为 8，剩下 [3, 8, 6]。
 * 合并 [3, 8, 6]，成本为 17，剩下 [17]。
 * 总成本 25，这是可能的最小值。
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1 <= stones.length <= 30
 * 2 <= K <= 30
 * 1 <= stones[i] <= 100
 *
 *
 */

// @lc code=start
class Solution
{
    static constexpr int inf = 0x3f3f3f3f;
public:
    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        if((n - 1) % (k - 1) != 0)
            return -1;
        
        vector<vector<int>> d(n, vector<int>(n, inf));
        vector<int> sum(n, 0);//前缀和
        for(int i = 0, s = 0; i < n; i++){
            d[i][i] = 0;
            s += stones[i];
            sum[i] = s;
        }

        //计算合并每种堆需要的最小代价，以此动态到[0,n-1]
        //其实原理就是，n堆必然会被分为k堆，每堆再分为k堆，所以可以用动态规划
        for(int len = 2; len <= n; len++){
            for(int l = 0; l < n && l + len - 1 < n; l++){
                int r = l + len - 1;
                for(int mid = l; mid < r; mid += k - 1){
                    d[l][r] = min(d[l][r], d[l][mid] + d[mid + 1][r]);
                }
                if((len - 1) % (k - 1) == 0)
                    d[l][r] += sum[r] - (l == 0 ? 0 : sum[l - 1]); // 加上此次本身的合并代价
            }
        }
        return d[0][n - 1];
    }
};
// @lc code=end
