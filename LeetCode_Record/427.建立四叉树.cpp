#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=427 lang=cpp
 *
 * [427] 建立四叉树
 */
// class Node
// {
// public:
//     bool val;
//     bool isLeaf;
//     Node *topLeft;
//     Node *topRight;
//     Node *bottomLeft;
//     Node *bottomRight;

//     Node()
//     {
//         val = false;
//         isLeaf = false;
//         topLeft = NULL;
//         topRight = NULL;
//         bottomLeft = NULL;
//         bottomRight = NULL;
//     }

//     Node(bool _val, bool _isLeaf)
//     {
//         val = _val;
//         isLeaf = _isLeaf;
//         topLeft = NULL;
//         topRight = NULL;
//         bottomLeft = NULL;
//         bottomRight = NULL;
//     }

//     Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
//     {
//         val = _val;
//         isLeaf = _isLeaf;
//         topLeft = _topLeft;
//         topRight = _topRight;
//         bottomLeft = _bottomLeft;
//         bottomRight = _bottomRight;
//     }
// };
// @lc code=start
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution
{
    vector<vector<int>> grid;
public:
    Node *construct(vector<vector<int>> &grid)
    {
        this->grid = grid;
        return dfs(0, grid.size() - 1, 0, grid.size() - 1);
    }

    Node *dfs(int x1, int x2, int y1, int y2)
    {
        int val = grid[x1][y1];
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                if (grid[i][j] != val)
                {
                    return new Node(
                        1,
                        false, 
                        dfs(x1, (x1 + x2) / 2, y1, (y1 + y2) / 2),
                        dfs(x1, (x1 + x2) / 2, (y1 + y2) / 2 + 1, y2),

                        dfs((x1 + x2) / 2 + 1, x2, y1, (y1 + y2) / 2),
                        dfs((x1 + x2) / 2 + 1, x2, (y1 + y2) / 2 + 1, y2));
                }
            }
        }
        return new Node(val, true);
    }
};
// @lc code=end
