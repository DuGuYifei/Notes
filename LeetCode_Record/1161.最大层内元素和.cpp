#include <vector>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*
 * @lc app=leetcode.cn id=1161 lang=cpp
 *
 * [1161] 最大层内元素和
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
public:
    vector<int> sum;
    void dfs(TreeNode *root, int level)
    {
        if(sum.size() == level)
        {
            sum.push_back(root->val);
        }
        else
        {
            sum[level] += root->val;
        }
        if(root->left)
            dfs(root->left, level + 1);
        if(root->right)
            dfs(root->right, level + 1);
    }
    int maxLevelSum(TreeNode *root)
    {
        dfs(root,0);
        int maxS = INT_MIN, level = -1;
        for(int i = 0; i < sum.size();i++)
        {
            if(sum[i] > maxS)
            {
                maxS = sum[i];
                level = i;
            }
        }
        return level + 1;
    }
};
// @lc code=end
