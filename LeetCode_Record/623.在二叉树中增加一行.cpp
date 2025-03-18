/*
 * @lc app=leetcode.cn id=623 lang=cpp
 *
 * [623] 在二叉树中增加一行
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    int level;
    void dfs(TreeNode* root, int val, int depth)
    {
        if(depth == level)
        {
            root->left = new TreeNode(val, root->left, nullptr);
            root->right = new TreeNode(val, nullptr, root->right);
            return;
        }
        if(root->left)
            dfs(root->left, val, depth+1);
        if(root->right)
            dfs(root->right, val, depth+1);
    }

    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        level = depth;
        if(depth == 1)
        {
            root = new TreeNode(val, root, nullptr);
        }
        else
            dfs(root, val, 2);
        return root;

    }
};
// @lc code=end

