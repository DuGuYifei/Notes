/*
 * @lc app=leetcode.cn id=754 lang=cpp
 *
 * [754] 到达终点数字
 *
 * https://leetcode-cn.com/problems/reach-a-number/description/
 *
 * algorithms
 * Medium (43.76%)
 * Likes:    205
 * Dislikes: 0
 * Total Accepted:    12.8K
 * Total Submissions: 28.2K
 * Testcase Example:  '2'
 *
 * 在一根无限长的数轴上，你站在0的位置。终点在target的位置。
 * 
 * 你可以做一些数量的移动 numMoves :
 * 
 * 
 * 每次你可以选择向左或向右移动。
 * 第 i 次移动（从  i == 1 开始，到 i == numMoves ），在选择的方向上走 i 步。
 * 
 * 
 * 给定整数 target ，返回 到达目标所需的 最小 移动次数(即最小 numMoves ) 。
 * 
 * 
 * 
 * 示例 1:
 * 
 * 
 * 输入: target = 2
 * 输出: 3
 * 解释:
 * 第一次移动，从 0 到 1 。
 * 第二次移动，从 1 到 -1 。
 * 第三次移动，从 -1 到 2 。
 * 
 * 
 * 示例 2:
 * 
 * 
 * 输入: target = 3
 * 输出: 2
 * 解释:
 * 第一次移动，从 0 到 1 。
 * 第二次移动，从 1 到 3 。
 * 
 * 
 * 
 * 
 * 提示:
 * 
 * 
 * -10^9 <= target <= 10^9
 * target != 0
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int reachNumber(int target) {
        target = target > 0 ? target : -target;
        int i = 1;
        int t = 0;
        while((t - target) < 0 || (t - target) % 2)
        {
            t += i;
            i++;
        }
        return i - 1;     
    }
};
// @lc code=end

