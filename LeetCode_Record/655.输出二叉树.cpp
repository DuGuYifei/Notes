#include <vector>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*
 * @lc app=leetcode.cn id=655 lang=cpp
 *
 * [655] 输出二叉树
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
public:
    int getHeight(TreeNode* root)
    {
        int h = 1;
        if(root->left)
            h = max(h, getHeight(root->left) + 1);
        if(root->right)
            h = max(h, getHeight(root->right) + 1);
        return h;
    }

    void dfs(vector<vector<string>>& ans, TreeNode* root, int h, int r, int c)
    {
        ans[r][c] = to_string(root->val);
        if(root->left)
            dfs(ans, root -> left, h, r + 1, c - (1 << (h - r - 2)));
        if(root->right)
            dfs(ans, root -> right, h, r + 1, c + (1 << (h - r - 2)));
    }

    vector<vector<string>> printTree(TreeNode* root) {
        int m = getHeight(root);
        int n = (1 << m) - 1;
        vector<vector<string>> ans(m, vector<string>(n, ""));
        dfs(ans, root, m, 0, (n-1)/2);
        return ans;
    }
};
// @lc code=end

