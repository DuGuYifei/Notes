#include<vector>
#include<string>
using namespace std;
/*
 * @lc app=leetcode.cn id=1598 lang=cpp
 *
 * [1598] 文件夹操作日志搜集器
 */

// @lc code=start
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth = 0;
        for(const auto& i:logs)
        {
            if(i[0] == '.')
            {
                if(i[1] == '.')
                    depth = depth > 0? depth - 1:0;
            }
            else
                depth++;
        }
        return depth;
    }
};
// @lc code=end

