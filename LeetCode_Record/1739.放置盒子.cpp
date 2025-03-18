#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1739 lang=cpp
 *
 * [1739] 放置盒子
 *
 * https://leetcode-cn.com/problems/building-boxes/description/
 *
 * algorithms
 * Hard (48.04%)
 * Likes:    38
 * Dislikes: 0
 * Total Accepted:    4.5K
 * Total Submissions: 8.6K
 * Testcase Example:  '3'
 *
 * 有一个立方体房间，其长度、宽度和高度都等于 n 个单位。请你在房间里放置 n 个盒子，每个盒子都是一个单位边长的立方体。放置规则如下：
 * 
 * 
 * 你可以把盒子放在地板上的任何地方。
 * 如果盒子 x 需要放置在盒子 y 的顶部，那么盒子 y 竖直的四个侧面都 必须 与另一个盒子或墙相邻。
 * 
 * 
 * 给你一个整数 n ，返回接触地面的盒子的 最少 可能数量。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：n = 3
 * 输出：3
 * 解释：上图是 3 个盒子的摆放位置。
 * 这些盒子放在房间的一角，对应左侧位置。
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 
 * 输入：n = 4
 * 输出：3
 * 解释：上图是 3 个盒子的摆放位置。
 * 这些盒子放在房间的一角，对应左侧位置。
 * 
 * 
 * 示例 3：
 * 
 * 
 * 
 * 
 * 输入：n = 10
 * 输出：6
 * 解释：上图是 10 个盒子的摆放位置。
 * 这些盒子放在房间的一角，对应后方位置。
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int minimumBoxes(int n) {
        int ans = 0;
        int i = 1;
        int cnt = 0;
        for(;cnt < n;i++){
            cnt += (i * i + i)/2;
            ans += i;
        }
        cnt -= --i;
        while(cnt >= n){
            ans--;
            cnt -= --i;
        }
        return ans;
    }
};
// @lc code=end

