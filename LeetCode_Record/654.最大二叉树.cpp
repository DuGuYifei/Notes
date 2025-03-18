#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=654 lang=cpp
 *
 * [654] 最大二叉树
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
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
private:
    TreeNode *ans;
    int n;

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        ans = new TreeNode(nums[0]);
        n = nums.size();
        if(n > 1)
            build(1, nums, ans);
        return ans;
    }

    void build(int idx, vector<int> &nums, TreeNode *root)
    {
        TreeNode *tmp = new TreeNode(nums[idx]);
        if (nums[idx] < root->val)
            root->right = tmp;
        else
        {
            TreeNode *r = ans;
            TreeNode* father = nullptr;
            while (r->val > nums[idx])
            {
                father = r;
                r = r->right;
            }
            tmp->left = r;
            if(father)
                father->right = tmp;
            else
                ans = tmp;
        }
        if(idx < n - 1)
            build(idx + 1, nums, tmp);
    }
};
// @lc code=end
