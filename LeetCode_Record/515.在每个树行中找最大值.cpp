#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=515 lang=cpp
 *
 * [515] 在每个树行中找最大值
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
//  struct TreeNode {
//      int val;
//      TreeNode *left;
//      TreeNode *right;
//      TreeNode() : val(0), left(nullptr), right(nullptr) {}
//      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  };
class Solution {
public:
    vector<int> ans;
    void dfs(TreeNode* root, int height)
    {
        if(!root)
            return;
        int t = root->val;
        if(ans.size() < height)
        {
            ans.push_back(t);
        }
        else
        {
            ans[height - 1] = max(ans[height - 1], t);
        }
        dfs(root->left,height+1);
        dfs(root->right, height+1);
    }
    vector<int> largestValues(TreeNode* root) {
        dfs(root, 1);
        return ans;
    }
};
// @lc code=end

