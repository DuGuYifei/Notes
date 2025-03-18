#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=388 lang=cpp
 *
 * [388] 文件的最长绝对路径
 */

// @lc code=start
class Solution
{
public:
    int lengthLongestPath(string input)
    {
        int n = input.size();
        int len = 0;
        int i = 0;
        bool file = false;
        // 获得第一层目录长度
        for (; i < n; i++)
        {
            if (input[i] == '.')
                file = true;
            if (input[i] == '\n')
                break;
            len++;
        }
        // 如果只有一层
        if (i == n)
            return file ? len : 0;
        file = false;
        int ans = 0;
        // 遍历
        vector<int> level(n);
        level[1] = len;
        int depth = 1;
        while (i < n)
        {
            if (input[i] == '.')
                file = true;
            if (input[i] != '\n')
            {
                len++;
                i++;
                continue;
            }
            i++;
            // 根据文件算长度
            if (file)
            {
                ans = max(ans, len);
                file = false;
            }

            // 计算长度n
            int depth_calculate = 0;
            while (input[i] == '\t')
            {
                depth_calculate++;
                i++;
            }
            if (depth_calculate == depth)
            {
                len++;
                level[depth_calculate - 1] = len;
                depth++;
            }
            else
            {
                if (depth_calculate > 0)
                    len = level[depth_calculate - 1];
                else
                    len = 0;
                depth = depth_calculate + 1;
            }
        }
        if (file)
        {
            ans = max(ans, len);
        }
        return ans;
    }
};
// @lc code=end
