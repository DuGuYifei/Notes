#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;
/*
 * @lc app=leetcode.cn id=1815 lang=cpp
 *
 * [1815] 得到新鲜甜甜圈的最多组数
 *
 * https://leetcode-cn.com/problems/maximum-number-of-groups-getting-fresh-donuts/description/
 *
 * algorithms
 * Hard (30.14%)
 * Likes:    43
 * Dislikes: 0
 * Total Accepted:    3.4K
 * Total Submissions: 9.3K
 * Testcase Example:  '3\n[1,2,3,4,5,6]'
 *
 * 有一个甜甜圈商店，每批次都烤 batchSize 个甜甜圈。这个店铺有个规则，就是在烤一批新的甜甜圈时，之前 所有
 * 甜甜圈都必须已经全部销售完毕。给你一个整数 batchSize 和一个整数数组 groups ，数组中的每个整数都代表一批前来购买甜甜圈的顾客，其中
 * groups[i] 表示这一批顾客的人数。每一位顾客都恰好只要一个甜甜圈。
 *
 * 当有一批顾客来到商店时，他们所有人都必须在下一批顾客来之前购买完甜甜圈。如果一批顾客中第一位顾客得到的甜甜圈不是上一组剩下的，那么这一组人都会很开心。
 *
 * 你可以随意安排每批顾客到来的顺序。请你返回在此前提下，最多 有多少组人会感到开心。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：batchSize = 3, groups = [1,2,3,4,5,6]
 * 输出：4
 * 解释：你可以将这些批次的顾客顺序安排为 [6,2,4,5,1,3] 。那么第 1，2，4，6 组都会感到开心。
 *
 *
 * 示例 2：
 *
 *
 * 输入：batchSize = 4, groups = [1,3,2,5,2,2,1,6]
 * 输出：4
 *
 *
 *
 *
 * 提示：
 *
 *
 * 1
 * 1
 * 1
 *
 *
 */

// @lc code=start
class Solution
{
private:
    static constexpr int kWidth = 5;
    static constexpr int kWidthMask = (1 << kWidth) - 1;
public:
    int maxHappyGroups(int batchSize, vector<int> &groups)
    {
        vector<int> cnt(batchSize);
        for(int x:groups)
        {
            cnt[x % batchSize]++;
        }
        long long start = 0;
        for(int i = batchSize - 1; i >= 1; i--)
        {
            start = (start << kWidth) | cnt[i];
        }
        unordered_map<long long, int> memo;
        function<int(long long)> dfs = [&](long long mask){
            if(mask == 0)
                return 0;
            if(memo.count(mask))
                return memo[mask];
            
            int total = 0;
            for(int i = 1; i < batchSize; i++)
            {
                int amount = ((mask >> ((i - 1) * kWidth)) & kWidthMask);
                total += i * amount;
            }

            int best = 0;
            for(int i = 1; i < batchSize; i++)
            {
                int amount = ((mask >> ((i - 1) * kWidth)) & kWidthMask);
                if(amount > 0){
                    int result = dfs(mask - (1LL << ((i - 1) * kWidth)));
                    if((total - i) % batchSize == 0)
                        result++;
                    best = max(best, result);
                }
            }
            return memo[mask] = best;
        };
        return dfs(start) + cnt[0];
    }
};
// @lc code=end
