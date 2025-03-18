#include <vector>
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
 * @lc app=leetcode.cn id=662 lang=cpp
 *
 * [662] 二叉树最大宽度
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
    // key1：dfs每层最先访问到的节点是该层最左侧节点
    // key2：可以直接 index 节点，左子：2*index，右子：2*index+1
    vector<unsigned long long> left;
    vector<unsigned long long> right;
    int widthOfBinaryTree(TreeNode* root) {
        dfs(root, 0, 1);
        unsigned long long maxi = 1;
        for(int i = 0; i < left.size(); i++)
        {
            int num = right[i] - left[i] + 1;
            if(right[i] != 0)
                maxi = maxi > num? maxi : num;
        }
        return maxi;
    }

    void dfs(TreeNode* root, int level, unsigned long long index)
    {
        if(left.size() <= level)
        {
            left.push_back(index);
            right.resize(left.size(), 0);
        }
        else
            right[level] = index;
        if(root->left)
            dfs(root->left, level + 1, index * 2);
        if(root->right)
            dfs(root->right, level + 1, index * 2 + 1);
    }
};
// @lc code=end

