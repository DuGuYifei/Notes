#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1305 lang=cpp
 *
 * [1305] 两棵二叉搜索树中的所有元素
 */
// struct TreeNode
// {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };
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
    void dfs(TreeNode *root, vector<int> &v)
    {
        if (root != nullptr)
        {
            dfs(root->left, v);
            v.push_back(root->val);
            dfs(root->right, v);
        }
    }
    vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
    {
        vector<int> a, b, ans;
        dfs(root1, a);
        dfs(root2, b);

        int n1 = a.size();
        int n2 = b.size();
        auto p1 = a.begin(), p2 = b.begin();
        while (true)
        {
            if (p1 == a.end())
            {
                ans.insert(ans.end(), p2, b.end());
                break;
            }
            if (p2 == b.end())
            {
                ans.insert(ans.end(), p1, a.end());
                break;
            }
            if(*p1 > *p2)
            {
                ans.push_back(*p2);
                p2++;
            }
            else
            {
                ans.push_back(*p1);
                p1++;
            }
        }
        return ans;
    }
};
// @lc code=end
