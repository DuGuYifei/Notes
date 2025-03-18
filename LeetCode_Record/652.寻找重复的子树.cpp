#include <vector>
#include <unordered_map>
#include <unordered_set>
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
 * @lc app=leetcode.cn id=652 lang=cpp
 *
 * [652] 寻找重复的子树
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
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return {ans.begin(), ans.end()};
    }

    int dfs(TreeNode* root)
    {
        if(!root)
            return 0;
        
        tuple<int,int,int> tp = tuple{root->val, dfs(root->left), dfs(root->right)};

        if(t_map.find(tp) != t_map.end())
        {
            ans.insert(t_map[tp].first);
            return t_map[tp].second;
        }
        else
        {
            t_map[tp] = {root, ++idx};
            return idx;
        }
    }

private:
    //关键1：这是给予每种子树一个单独的idx
    int idx = 0;
    
    // 关键2.1: hash表   存储tuple 和 节点TreeNode 以及 它的idx 用于遇到相同的子树时将其转化为idx
    // 关键2.2: hash集合 存储重复子树的其中一个
    static constexpr auto hash_t = [fn = hash<int>()](const tuple<int,int,int>& t)->size_t{
        auto &[x,y,z] = t;
        return fn(x)<< 16 ^ fn(y) << 8 ^ fn(z);
    };
    unordered_map<tuple<int,int,int>, pair<TreeNode*, int>, decltype(hash_t)> t_map{0, hash_t};
    unordered_set<TreeNode*> ans;
};
// @lc code=end

