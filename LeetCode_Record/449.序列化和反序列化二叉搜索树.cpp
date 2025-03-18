#include <string>
#include <vector>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*
 * @lc app=leetcode.cn id=449 lang=cpp
 *
 * [449] 序列化和反序列化二叉搜索树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Codec
{
public:
    int index = 1;
    int n = 0;
    vector<int> nums;
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string ans = "";
        if (root == nullptr)
            return ans;
        dfs(ans,root);
        return ans;
    }

    void dfs(string& ans, TreeNode* root)
    {
        if(root == nullptr)
            return;
        ans += to_string(root->val) + ",";
        dfs(ans,root->left);
        dfs(ans,root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        if(data == "")
            return 0;
        
        for (int i = 0; i < data.size(); i++)
        {
            string temp = "";
            while (data[i] != ',')
            {
                temp.append(1, data[i++]);
            }
            nums.push_back(stoi(temp));
        }
        n = nums.size();
        TreeNode* root = new TreeNode(nums[0]);
        //int n = nums.size();
        de_helper(root,INT_MAX);
        return root;
    }

    void de_helper(TreeNode* root, int val)
    {
        if(index >= n)
            return;
        if(nums[index]<root->val)
        {
            TreeNode* left = new TreeNode(nums[index]);
            index += 1;
            de_helper(left,root->val);
            root->left = left;
        }
        if(index >= nums.size()||nums[index]>val)
            return;
        TreeNode* right = new TreeNode(nums[index]);
        index += 1;
        de_helper(right,val);
        root->right = right;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
// @lc code=end
