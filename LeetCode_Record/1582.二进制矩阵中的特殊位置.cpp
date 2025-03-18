#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1582 lang=cpp
 *
 * [1582] 二进制矩阵中的特殊位置
 */

// @lc code=start
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int res = 0;
        for(int i =0;i<m;i++)
        {
            int col = -1;
            bool success = false;
            for(int j = 0; j < n;j++)
            {
                if(mat[i][j])
                {
                    if(success)
                    {
                        success = false;
                        break;
                    }
                    success = true;
                    col = j;
                }
            }
            if(success)
            {
                success = false;
                for(int k = 0; k < m;k++)
                {
                    if(mat[k][col])
                    {
                        if(success)
                        {
                            success = false;
                            break;
                        }
                        success = true;
                    }
                }
                if(success)
                    res++;
            }
        }
        return res;
    }
};
// @lc code=end

