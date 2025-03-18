import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

/*
 * @lc app=leetcode.cn id=1129 lang=java
 *
 * [1129] 颜色交替的最短路径
 *
 * https://leetcode-cn.com/problems/shortest-path-with-alternating-colors/description/
 *
 * algorithms
 * Medium (39.04%)
 * Likes:    130
 * Dislikes: 0
 * Total Accepted:    11.5K
 * Total Submissions: 27.6K
 * Testcase Example:  '3\n[[0,1],[1,2]]\n[]'
 *
 * 在一个有向图中，节点分别标记为 0, 1, ..., n-1。图中每条边为红色或者蓝色，且存在自环或平行边。
 * 
 * red_edges 中的每一个 [i, j] 对表示从节点 i 到节点 j 的红色有向边。类似地，blue_edges 中的每一个 [i, j]
 * 对表示从节点 i 到节点 j 的蓝色有向边。
 * 
 * 返回长度为 n 的数组 answer，其中 answer[X] 是从节点 0 到节点 X
 * 的红色边和蓝色边交替出现的最短路径的长度。如果不存在这样的路径，那么 answer[x] = -1。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：n = 3, red_edges = [[0,1],[1,2]], blue_edges = []
 * 输出：[0,1,-1]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：n = 3, red_edges = [[0,1]], blue_edges = [[2,1]]
 * 输出：[0,1,-1]
 * 
 * 
 * 示例 3：
 * 
 * 
 * 输入：n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
 * 输出：[0,-1,-1]
 * 
 * 
 * 示例 4：
 * 
 * 
 * 输入：n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
 * 输出：[0,1,2]
 * 
 * 
 * 示例 5：
 * 
 * 
 * 输入：n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
 * 输出：[0,1,1]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= n <= 100
 * red_edges.length <= 400
 * blue_edges.length <= 400
 * red_edges[i].length == blue_edges[i].length == 2
 * 0 <= red_edges[i][j], blue_edges[i][j] < n
 * 
 * 
 */

// @lc code=start
class Solution {
    public int[] shortestAlternatingPaths(int n, int[][] redEdges, int[][] blueEdges) {
        HashMap<Integer, ArrayList<Integer>> redges = new HashMap<>();
        HashMap<Integer, ArrayList<Integer>> bedges = new HashMap<>();
        for (int[] i : redEdges)
        {
            redges.putIfAbsent(i[0], new ArrayList<>());
            redges.get(i[0]).add(i[1]);
        }
        for (int[] i : blueEdges)
        {
            bedges.putIfAbsent(i[0], new ArrayList<>());
            bedges.get(i[0]).add(i[1]);
        }
        Queue<Integer> visited_red = new LinkedList<>();
        Queue<Integer> visited_blue = new LinkedList<>();
        int[] visited_color = new int[n]; // 0 no visit, 01 blue, 10 red, 11 both
        int[] dismap = new int[n];
        Arrays.fill(dismap, -1);
        visited_color[0] = 3;
        for (Integer i : redges.getOrDefault(0, new ArrayList<>()))
        {
            visited_red.add(i);
            dismap[i] = 1;
            visited_color[i] |= 2;
        }
        for (Integer i : bedges.getOrDefault(0, new ArrayList<>()))
        {
            visited_blue.add(i);
            dismap[i] = 1;
            visited_color[i] |= 1;
        }
        dismap[0] = 0;
        int dis = 2;
        while (!(visited_blue.isEmpty() && visited_red.isEmpty()))
        {
            int nr = visited_red.size();
            int nb = visited_blue.size();
            while (nr > 0)
            {
                nr--;
                int t = visited_red.poll();
                for (Integer next : bedges.getOrDefault(t, new ArrayList<>()))
                {
                    if ((visited_color[next] & 1) == 1)
                        continue;
                    visited_color[next] |= 1;
                    visited_blue.add(next);
                    if (dismap[next] == -1)
                        dismap[next] = dis;
                }
            }
            while (nb > 0)
            {
                nb--;
                int t = visited_blue.poll();
                for (Integer next : redges.getOrDefault(t, new ArrayList<>()))
                {
                    if ((visited_color[next] & 2) == 2)
                        continue;
                    visited_color[next] |= 2;
                    visited_red.add(next);
                    if (dismap[next] == -1)
                        dismap[next] = dis;
                }
            }
            dis++;
        }
        return dismap;
    }
}
// @lc code=end

