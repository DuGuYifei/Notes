struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*
 * @lc app=leetcode.cn id=669 lang=cpp
 *
 * [669] 修剪二叉搜索树
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
class Solution {
private:
    int low, high;
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        this->low = low;
        this->high = high;

        root = dfs(root);
        return root;
    }

    TreeNode* dfs(TreeNode* root)
    {
        if(!root)
            return nullptr;
        
        if(root->val < low)
            return dfs(root->right);
        else if(root->val > high)
            return dfs(root->left);

        root->left = dfs(root->left);
        root->right = dfs(root->right);
        return root;
    }
};
// @lc code=end

