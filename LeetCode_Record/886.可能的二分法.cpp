#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=886 lang=cpp
 *
 * [886] 可能的二分法
 *
 * https://leetcode-cn.com/problems/possible-bipartition/description/
 *
 * algorithms
 * Medium (46.84%)
 * Likes:    214
 * Dislikes: 0
 * Total Accepted:    22.8K
 * Total Submissions: 45.6K
 * Testcase Example:  '4\n[[1,2],[1,3],[2,4]]'
 *
 * 给定一组 n 人（编号为 1, 2, ..., n）， 我们想把每个人分进任意大小的两组。每个人都可能不喜欢其他人，那么他们不应该属于同一组。
 * 
 * 给定整数 n 和数组 dislikes ，其中 dislikes[i] = [ai, bi] ，表示不允许将编号为 ai 和
 * bi的人归入同一组。当可以用这种方法将所有人分进两组时，返回 true；否则返回 false。
 * 
 * 
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 4, dislikes = [[1,2],[1,3],[2,4]]
 * 输出：true
 * 解释：group1 [1,4], group2 [2,3]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 3, dislikes = [[1,2],[1,3],[2,3]]
 * 输出：false
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 2000
 * 0 <= dislikes.length <= 10^4
 * dislikes[i].length == 2
 * 1 <= dislikes[i][j] <= n
 * ai < bi
 * dislikes 中每一组都 不同
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool dfs(vector<int>& colors, int val, vector<vector<int>>& maps)
    {
        int color = -1 * colors[val];
        for(auto& i: maps[val])
        {
            if(colors[i])
            {
                if(colors[i] != color)
                    return false;
            }
            else
            {
                colors[i] = color;
                if(!dfs(colors, i, maps)) return false;
            }
        }
        return true;
    }
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> maps(n + 1);
        for(auto& i : dislikes)
        {
            maps[i[0]].push_back(i[1]);
            maps[i[1]].push_back(i[0]); 
            // 一定得双向，因为 1-4 3-5 4-5 时，会先发现3没有颜色，于是上色1结果5就必须在3的对立面，此时其实3时-1就对了
            // 双向则会让5自动先给3附上色
        }
        vector<int> colors(n + 1, 0);
        for(int i = 1;i <= n; i++)
        {
            if(!colors[i])
            {
                colors[i]  = 1;
                if(!dfs(colors, i, maps))
                    return false;
            }
        }
        return true;
    }
};
// @lc code=end

