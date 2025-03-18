#include <vector>
using namespace std;

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<bool> row(m, false);
        vector<bool> col(n, false);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (!matrix[i][j])
                {
                    col[j] = true;
                    row[i] = true;
                }

        for(int i = 0;i < m; i++)
            for(int j = 0; j < n; j++)
                if(row[i] || col[j])
                    matrix[i][j] = 0;
        
        // int r = row.size();
        // int c = col.size();
        // for(int i = 0; i < r; i++)
        // {
        //     if(row[i])
        //     {
        //         for(int j = 0; j < n; j++)
        //         {
        //             matrix[i][j] = 0;
        //         }
        //     }
        // }
        // for(int j = 0; j < c; j++)
        // {
        //     if(col[j])
        //     {
        //         for(int i = 0; i< m; i++)
        //         {
        //             matrix[i][j] = 0;
        //         }
        //     }
        // }
    }
};