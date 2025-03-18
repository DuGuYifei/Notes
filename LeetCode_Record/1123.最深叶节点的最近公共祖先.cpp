#include <algorithm>
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
 * @lc app=leetcode.cn id=1123 lang=cpp
 *
 * [1123] 最深叶节点的最近公共祖先
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
    TreeNode* ans;
    int wholeDepth = 0;
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        deepestHelper(root, 0);
        return ans;
    }
    int deepestHelper(TreeNode* root, int depth) {
        int deepestLeft = depth;
        int deepestRight = depth;
        if (root->left) {
            deepestLeft = deepestHelper(root->left, depth + 1);
        }
        if (root->right) {
            deepestRight = deepestHelper(root->right, depth + 1);
        }
        int deepest = max(deepestLeft, deepestRight);
        if (deepestLeft == deepestRight && deepest >= wholeDepth) {
            ans = root;
            wholeDepth = deepest;
        }
        return deepest;
    }
};
// @lc code=end

