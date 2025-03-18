/*
 * @lc app=leetcode.cn id=1110 lang=cpp
 *
 * [1110] 删点成林
 *
 * https://leetcode.cn/problems/delete-nodes-and-return-forest/description/
 *
 * algorithms
 * Medium (64.88%)
 * Likes:    291
 * Dislikes: 0
 * Total Accepted:    35.2K
 * Total Submissions: 50.7K
 * Testcase Example:  '[1,2,3,4,5,6,7]\n[3,5]'
 *
 * 给出二叉树的根节点 root，树上每个节点都有一个不同的值。
 * 
 * 如果节点值在 to_delete 中出现，我们就把该节点从树上删去，最后得到一个森林（一些不相交的树构成的集合）。
 * 
 * 返回森林中的每棵树。你可以按任意顺序组织答案。
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 
 * 
 * 输入：root = [1,2,3,4,5,6,7], to_delete = [3,5]
 * 输出：[[1,2,null,4],[6],[7]]
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：root = [1,2,4,null,3], to_delete = [3]
 * 输出：[[1,2,4]]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 树中的节点数最大为 1000。
 * 每个节点都有一个介于 1 到 1000 之间的值，且各不相同。
 * to_delete.length <= 1000
 * to_delete 包含一些从 1 到 1000、各不相同的值。
 * 
 * 
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
    vector<TreeNode*> res;
    bool to_delete[1001];
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        for(int& i : to_delete){
            this->to_delete[i] = true;
        }
        dfs(root, nullptr, false, true);
        return res;
    }
    void dfs(TreeNode* root, TreeNode* parent, bool isLeft, bool parentNotPush){
        if(!to_delete[root->val]){
            if(parentNotPush){
                res.emplace_back(root);
                parentNotPush = false;
            }
        }else{
            if(parent != nullptr){
                if(isLeft)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            parentNotPush = true;
        }
        if(root->left)
            dfs(root->left, root, true, parentNotPush);
        if(root->right)
            dfs(root->right, root, false, parentNotPush);
    }
};
// @lc code=end

