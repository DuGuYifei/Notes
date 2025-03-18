#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=2044 lang=cpp
 *
 * [2044] 统计按位或能得到最大值的子集数目
 */

// @lc code=start
// class Solution
// {
// public:
//     int countMaxOrSubsets(vector<int> &nums)
//     {
//         // 状态压缩
//         int n = nums.size(), cnt = 0, maxValue = 0, stateNum = 1 << n; // 2^n : 索引0是空集
//         for (int i = 1; i < stateNum; i++)
//         {
//             int curValue = 0;
//             // j 是第j位的数字
//             for (int j = 0; j < n; j++)
//             {
//                 int x = i >>j;
//                 if(x == 0) break;
//                 if ((x & 1) == 1)
//                 {
//                     curValue |= nums[j];
//                 }
//             }
//             if (curValue == maxValue)
//                 cnt++;
//             else if (curValue > maxValue)
//             {
//                 maxValue = curValue;
//                 cnt = 1;
//             }
//         }

//         return cnt;
//     }
// };

// 用记忆搜索会更快，因为其实相同后面相同只是第一位不同的数字没必要再从头算起，只算最前面的位即可
// 用人话说就是：从nums[0]开始选择要或者不要，每一个来一遍，并且这是回溯，会记住上一个答案，就比状态压缩快
class Solution
{
private:
    vector<int> num;
    int cnt = 0;
    int maxVal = 0;
    int n;

public:
    int countMaxOrSubsets(vector<int> &nums)
    {
        n = nums.size();
        num = nums;
        dfs(0, 0);
        return cnt;
    }

    void dfs(int pos, int curValue)
    {
        if (pos == n)
        {
            if (curValue == maxVal)
                cnt++;
            else if (curValue > maxVal)
            {
                maxVal = curValue;
                cnt = 1;
            }
            return;
        }
        // 当前位为0
        dfs(pos + 1, curValue);
        // 当前位为1
        dfs(pos + 1, curValue | num[pos]);
    }
};
// @lc code=end
