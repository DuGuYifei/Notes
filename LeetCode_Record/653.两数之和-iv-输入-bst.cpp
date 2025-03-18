#include <unordered_set>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=653 lang=cpp
 *
 * [653] 两数之和 IV - 输入 BST
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
    //unordered_set<int> repository;
    vector<int> repository;
public:
    void storeNumbers(TreeNode* root)
    {
        if(root == nullptr)
            return;
        storeNumbers(root->left);
        repository.push_back(root->val);
        storeNumbers(root->right);
    }

    bool findTarget(TreeNode *root, int k)
    {
        // DFS
        // if (root == nullptr)
        //     return false;
        // if (repository.count(k - root->val))
        //     return true;
        // repository.insert(root->val);
        // return findTarget(root->left, k) || findTarget(root->right, k);

        // 先将其变成顺序递增数列再双指针查找
        storeNumbers(root);
        int left = 0;
        int right = repository.size() - 1;
        while(left<right)
        {
            int sum = repository[left] + repository[right];
            if(sum == k)
                return true;
            if(sum>k)
                right--;
            else
                left++;
        }
        return false;
    }
};
// @lc code=end
