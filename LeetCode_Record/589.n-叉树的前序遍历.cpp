#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=589 lang=cpp
 *
 * [589] N 叉树的前序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution
{
public:
    vector<int> ans;
    vector<int> preorder(Node *root)
    {
        if(root == nullptr)
            return ans;
        dfs(root);
        return ans;
    }
    void dfs(Node *root)
    {
        ans.push_back(root->val);
        for (auto& i : root->children)
        {
            dfs(i);
        }
        return;
    }
};
// @lc code=end
