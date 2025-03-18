#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=89 lang=cpp
 *
 * [89] 格雷编码
 */

// @lc code=start
class Solution {
public:
//00 01  11 10
//000 001   011 010   110 111 101 100
    //n+1位格雷码的集合 = n位格雷码集合(顺序)加前缀0 + n位格雷码集合(逆序)加前缀1  百度百科
    vector<int> grayCode(int n) {
        vector<int>res(1<<n);
        // for(int i = 0 ; i<(1<<n);i++)
        // {
        //     res[i] = (i>>1)^i;
        // }
        // return res;
        res[0]=0;
        for(int i = 0; i<n ;i ++)
        {
            int mid = (1 << i);
            for(int j = 0;j<(1<<i);j++)
            {
                res[mid+j]=res[mid-j-1] ^ (1<<i);
            }
        } 
        return res;       
    }
    
};
// @lc code=end

