struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution
{
public:
    int val;
    TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
    {
        TreeNode* successor = nullptr;
        if(p->right != nullptr)
        {
            successor = p->right;
            while(successor->left!=nullptr)
            {
                successor = successor->left;
            }
            return successor;
        }
        while(root != nullptr)
        {
            if(root->val > p->val)
            {
                successor = root;
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }
        return successor;
    }
};