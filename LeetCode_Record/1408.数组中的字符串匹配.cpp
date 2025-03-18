#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1408 lang=cpp
 *
 * [1408] 数组中的字符串匹配
 */

// @lc code=start

// KMP算法============================================
class Solution
{
public:
    vector<string> stringMatching(vector<string> &words)
    {
        int n = words.size();
        vector<string> ans;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (i != j && words[j].find(words[i]) != string::npos)
                {
                    ans.push_back(words[i]); //move(words[i])节省空间
                    break;
                }
            }
        return ans;
    }
};

// AC自动机===================================================
//不好用，因为这里是向要push子字符串，而且还不能包含自己，所以不方便
// #define ALPHABET 26

// class ACM
// {
// public:
//     struct Node
//     {
//         Node* child[ALPHABET];
//         Node* fail = nullptr;
//         vector<int>exist;
//     };

//     Node* root;
//     unordered_set<string> ans;
//     ACM(vector<string> &P)
//     {
//         root = new Node();
//         int n = P.size();
//         for (int i = 0; i < n; i++)
//         {
//             trie_insert(P[i]);
//         }

//         queue<Node*> q;

//         // 将第一层的fail直接设置为root
//         for (int i = 0; i < ALPHABET; i++)
//         {
//             if (root->child[i])
//             {
//                 root->child[i]->fail = root;
//                 q.push(root->child[i]);
//             }
//         }

//         while (!q.empty())
//         {
//             Node* x = q.front();
//             q.pop();
//             for (int i = 0; i < ALPHABET; i++)
//             {
//                 if (x->child[i])
//                 {
//                     Node* y = x->child[i];
//                     Node* fafail = x->fail;
//                     // x儿子的fail指针是x的fail下同样的儿子，如果不存在一样的儿子，就x的fail的fail直至root。
//                     //    ▼ 这里是为了root没有fail
//                     while (fafail && fafail->child[i] == nullptr)
//                     {
//                         fafail = fafail->fail;
//                     }
//                     if (fafail == nullptr)
//                         y->fail = root;
//                     else
//                         y->fail = fafail->child[i];

//                     if (y->fail->exist.size())
//                     {
//                         // y的fail和y同后缀，且y包含y的fail，所以
//                         for (int j = 0; j < y->fail->exist.size(); j++)
//                         {
//                             y->exist.push_back(y->fail->exist[j]);
//                         }
//                     }
//                     q.push(y);
//                 }
//             }
//         }
//     }

//     void trie_insert(string word)
//     {
//         Node* tmp = root;

//         int n = word.size();
//         for (int i = 0; i < n; i++)
//         {
//             int c = word[i] - 'a';
//             if (tmp->child[c] == nullptr)
//                 tmp->child[c] = new Node();
//             tmp = tmp->child[c];
//         }
//         tmp->exist.push_back(n);
//     }

//     void ac_query(string T)
//     {
//         Node* tmp = root;
//         for (int i = 0; i < T.size(); i++)
//         {
//             int c = T[i] - 'a';
//             //没有c就一直向上找， 直至找到；或者到了root都没找不到就放弃
//             while (tmp->child[c] == nullptr && tmp->fail)
//                 tmp = tmp->fail;
//             if (tmp->child[c])
//                 tmp = tmp->child[c];
//             else
//                 continue;

//             if (tmp->exist.size())
//             {
//                 for (int& j : tmp->exist)
//                 {
//                     string tempS = T.substr(i - j + 1, j);
//                     if(tempS != T)
//                     ans.emplace(tempS);
//                 }
//             }
//         }
//     }
// };
// class Solution
// {
// public:
//     vector<string> stringMatching(vector<string> &words)
//     {
//         int n = words.size();
//         vector<string> ans;
//         ACM acm(words);
//         for (const auto& i: words)
//         {
//             acm.ac_query(i);
//         }
//         for(const auto& i : acm.ans)
//             ans.push_back(i);
//         return ans;
//     }
// };
// @lc code=end
