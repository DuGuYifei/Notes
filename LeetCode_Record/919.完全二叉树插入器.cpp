#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=919 lang=cpp
 *
 * [919] 完全二叉树插入器
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

// 方法1-----------------------------------------------
// class CBTInserter
// {
// private:
//     TreeNode *root;
//     queue<TreeNode *> qu;

// public:
//     CBTInserter(TreeNode *root)
//     {
//         this->root = root;
//         queue<TreeNode*> q;
//         q.push(root);
//         while(!q.empty())
//         {
//             TreeNode* node = q.front();
//             q.pop();
//             if(node->left)
//                 q.push(node->left);
//             if(node->right)
//             {
//                 q.push(node->right);
//             }
//             if(!(node->left && node->right))
//                 qu.push(node);
//         }
//     }

//     int insert(int val)
//     {
//         TreeNode *child = new TreeNode(val);
//         TreeNode *node = qu.front();
//         int ans = node->val;
//         if (!node->left)
//             node->left = child;
//         else
//         {
//             node->right = child;
//             qu.pop();
//         }
//         qu.push(child);
//         return ans;
//     }

//     TreeNode *get_root()
//     {
//         return root;
//     }
// };

// 方法2-----------------------------------------------------
class CBTInserter {
private:
    TreeNode* root;
    int cnt  = 0;
public:
    CBTInserter(TreeNode* root) {
        this->root = root;

        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            ++cnt;
            TreeNode* node = q.front();
            q.pop();
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
    }
    
    int insert(int val) {
        cnt++;
        int i = 4, level = 0;
        while(i <= cnt)
        {
            level++;
            i*=2;
        }
        TreeNode* node = root;
        while(level > 0)
        {
            int c = cnt >> level;
            if( (c&1) == 1)
            {
                node = node -> right;
            }
            else
               node = node->left;
            level--;
        }
        int ans = node->val;

        if((cnt & 1) ==1)
            node->right = new TreeNode(val);
        else
            node->left = new TreeNode(val);
        return ans;
    }
    
    TreeNode* get_root() {
        return root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
// @lc code=end
