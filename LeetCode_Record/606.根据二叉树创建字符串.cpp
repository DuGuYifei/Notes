#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=606 lang=cpp
 *
 * [606] 根据二叉树创建字符串
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

class Solution
{
    string ans = "";

public:
    string tree2str(TreeNode *root)
    {
        dfs(root,true);
        return ans;
    }
    void dfs(TreeNode *root, bool isLeft)
    {
        if (root == nullptr)
            return;
        ans += to_string(root->val);
        bool leftNull = root->left == nullptr;
        bool rightNull = root->right == nullptr;
        if (leftNull)
        {
            if (rightNull)
            {
                return;
            }
            ans += "()(";
            dfs(root->right, false);
            ans += ")";
        }
        else
        {
            ans += "(";
            dfs(root->left, true);
            ans += ")";
            if (rightNull)
            {
                return;
            }
            ans += "(";
            dfs(root->right, false);
            ans += ")";
        }
    }
};
// @lc code=end