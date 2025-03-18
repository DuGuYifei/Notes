import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;

/*
 * @lc app=leetcode.cn id=1145 lang=java
 *
 * [1145] 二叉树着色游戏
 *
 * https://leetcode-cn.com/problems/binary-tree-coloring-game/description/
 *
 * algorithms
 * Medium (47.21%)
 * Likes:    195
 * Dislikes: 0
 * Total Accepted:    24.8K
 * Total Submissions: 44.6K
 * Testcase Example:  '[1,2,3,4,5,6,7,8,9,10,11]\n11\n3'
 *
 * 有两位极客玩家参与了一场「二叉树着色」的游戏。游戏中，给出二叉树的根节点 root，树上总共有 n 个节点，且 n 为奇数，其中每个节点上的值从 1 到
 * n 各不相同。
 * 
 * 最开始时：
 * 
 * 
 * 「一号」玩家从 [1, n] 中取一个值 x（1 <= x <= n）；
 * 「二号」玩家也从 [1, n] 中取一个值 y（1 <= y <= n）且 y != x。
 * 
 * 
 * 「一号」玩家给值为 x 的节点染上红色，而「二号」玩家给值为 y 的节点染上蓝色。
 * 
 * 之后两位玩家轮流进行操作，「一号」玩家先手。每一回合，玩家选择一个被他染过色的节点，将所选节点一个 未着色
 * 的邻节点（即左右子节点、或父节点）进行染色（「一号」玩家染红色，「二号」玩家染蓝色）。
 * 
 * 如果（且仅在此种情况下）当前玩家无法找到这样的节点来染色时，其回合就会被跳过。
 * 
 * 若两个玩家都没有可以染色的节点时，游戏结束。着色节点最多的那位玩家获得胜利 ✌️。
 * 
 * 现在，假设你是「二号」玩家，根据所给出的输入，假如存在一个 y 值可以确保你赢得这场游戏，则返回 true ；若无法获胜，就请返回 false 。
 * 
 * 
 * 示例 1 ：
 * 
 * 
 * 输入：root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
 * 输出：true
 * 解释：第二个玩家可以选择值为 2 的节点。
 * 
 * 示例 2 ：
 * 
 * 
 * 输入：root = [1,2,3], n = 3, x = 1
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中节点数目为 n
 * 1 <= x <= n <= 100
 * n 是奇数
 * 1 <= Node.val <= n
 * 树中所有值 互不相同
 * 
 * 
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    // public class TreeNode {
    //     int val;
    //     TreeNode left;
    //     TreeNode right;
    //     TreeNode() {}
    //     TreeNode(int val) { this.val = val; }
    //     TreeNode(int val, TreeNode left, TreeNode right) {
    //         this.val = val;
    //         this.left = left;
    //         this.right = right;
    //     }
    // }

    private HashMap<Integer, int[]> statis = new HashMap<>();
    List<Integer> list = new ArrayList<>();
    int p1;
    int xv;

    public boolean btreeGameWinningMove(TreeNode root, int n, int x) {
        xv = x;
        dfs(root, 1);
        for (Integer i : list)
        {
            if (!statis.containsKey(i / 2))
                statis.get(i)[2] = 0;
            else
            {
                if (i % 2 != 0)
                    statis.get(i)[2] = statis.get(i / 2)[0] + statis.get(i / 2)[2] + 1;
                else 
                    statis.get(i)[2] = statis.get(i / 2)[1] + statis.get(i / 2)[2] + 1;
            }
        }
        if (statis.get(p1)[2] + statis.get(p1)[0] + 1 < statis.get(p1)[1] || statis.get(p1)[2] + statis.get(p1)[1] + 1 < statis.get(p1)[0] || statis.get(p1)[0] + statis.get(p1)[1] + 1 < statis.get(p1)[2])
            return true;
        return false;
    }

    int dfs(TreeNode cur, int node)
    {
        if(cur.val == xv){
            p1 = node;
        }
        list.add(node);
        statis.put(node, new int[3]);
        statis.get(node)[0] = 0;
        statis.get(node)[1] = 0;
        if (cur.left != null)
            statis.get(node)[0] = dfs(cur.left, node * 2);
        if (cur.right != null)
            statis.get(node)[1] = dfs(cur.right, node * 2 + 1);
        return statis.get(node)[0] + statis.get(node)[1] + 1;
    }
}
// @lc code=end

