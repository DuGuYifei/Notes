#include <vector>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N 叉树的层序遍历
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

// class Solution {
//     vector<vector<int>> ans;
// public:
//     vector<vector<int>> levelOrder(Node* root) {
//         if(root == nullptr)
//             return ans;
//         ans.push_back(vector<int>{root->val});
//         bfs(root, 1);
//         return ans;
//     }
//     void bfs(Node* root, int height)
//     {
//         if(root->children.size() == 0)
//             return;

//         if(ans.size() - 1 < height)
//         {
//             ans.push_back(vector<int>());
//         }
//         for(Node* i : root->children)
//         {
//             ans[height].push_back(i->val);
//             bfs(i,height + 1);
//         }
//     }
//};

class Solution{
public:
    vector<vector<int>> levelOrder(Node* root)
    {
        vector<vector<int>> ans;
        if(root == nullptr)
             return ans;
        //ans.push_back(vector<int>{root->val});

        queue<Node*> wait;

        wait.push(root);
        // while(!wait.empty())
        // {
        //     int n = wait.size();
        //     vector<int> thisLevel;
        //     for(int i = 0;i<n;i++)
        //     {
        //         for(Node* i: wait.front()->children)
        //         {
        //             thisLevel.push_back(i->val);
        //             wait.push(i);
        //         }
        //         wait.pop();
        //     }
        //     if(!thisLevel.empty())
        //         ans.push_back(thisLevel);
        // }
        while(!wait.empty())
        {
            int n = wait.size();
            vector<int> thisLevel;
            for(int i = 0;i<n;i++)
            {
                Node* f = wait.front();
                thisLevel.push_back(f->val);
                for(Node* i: f->children)
                {
                    wait.push(i);
                }
                wait.pop();
            }
            //if(!thisLevel.empty())
                ans.push_back(move(thisLevel));
        }
        return ans;
    }
};

// @lc code=end

