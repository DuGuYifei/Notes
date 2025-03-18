#include <numeric>;
/*
 * @lc app=leetcode.cn id=1401 lang=cpp
 *
 * [1401] 圆和矩形是否有重叠
 *
 * https://leetcode-cn.com/problems/circle-and-rectangle-overlapping/description/
 *
 * algorithms
 * Medium (42.28%)
 * Likes:    46
 * Dislikes: 0
 * Total Accepted:    5.5K
 * Total Submissions: 12.8K
 * Testcase Example:  '1\n0\n0\n1\n-1\n3\n1'
 *
 * 给你一个以 (radius, x_center, y_center) 表示的圆和一个与坐标轴平行的矩形 (x1, y1, x2, y2)，其中 (x1,
 * y1) 是矩形左下角的坐标，(x2, y2) 是右上角的坐标。
 * 
 * 如果圆和矩形有重叠的部分，请你返回 True ，否则返回 False 。
 * 
 * 换句话说，请你检测是否 存在 点 (xi, yi) ，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 输入：radius = 1, x_center = 0, y_center = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
 * 输出：true
 * 解释：圆和矩形有公共点 (1,0) 
 * 
 * 
 * 示例 2：
 * 
 * 
 * 
 * 输入：radius = 1, x_center = 0, y_center = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
 * 输出：true
 * 
 * 
 * 示例 3：
 * 
 * 
 * 
 * 输入：radius = 1, x_center = 1, y_center = 1, x1 = -3, y1 = -3, x2 = 3, y2 = 3
 * 输出：true
 * 
 * 
 * 示例 4：
 * 
 * 输入：radius = 1, x_center = 1, y_center = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= radius <= 2000
 * -10^4 <= x_center, y_center, x1, y1, x2, y2 <= 10^4
 * x1 < x2
 * y1 < y2
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int a = pow(x1 - xCenter, 2);
        int b = pow(x2 - xCenter, 2);
        int m = pow(y1 - yCenter, 2);
        int n = pow(y2 - yCenter, 2);
        int r = radius * radius;
        if(a + m <= r || a + n <= r || b + m <= r || b + n <= r)
            return true;
        if(x1 <= xCenter + radius && x2 >= xCenter - radius && y1 <= yCenter && y2 >= yCenter)
            return true;
        if(y1 <= yCenter + radius && y2 >= yCenter - radius && x1 <= xCenter && x2 >= xCenter)
            return true;
        return false;
    }
};
// @lc code=end

