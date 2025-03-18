/*
 * @lc app=leetcode.cn id=780 lang=cpp
 *
 * [780] 到达终点
 */

// @lc code=start
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if(tx == sx && ty == sy) return true;
        if(sy > ty || sx > tx) return false; // 因为都大于1
        if(ty == sy) return !((tx - sx) % ty);
        if(tx == sx) return !((ty - sy) % tx);
        // 剩余 tx > sx && ty > sy
        return tx >= ty? reachingPoints(sx, sy, tx%ty,ty) : reachingPoints(sx,sy,tx,ty%tx);
    }
};
// @lc code=end

