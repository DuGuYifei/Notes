#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=902 lang=cpp
 *
 * [902] 最大为 N 的数字组合
 *
 * https://leetcode-cn.com/problems/numbers-at-most-n-given-digit-set/description/
 *
 * algorithms
 * Hard (34.99%)
 * Likes:    124
 * Dislikes: 0
 * Total Accepted:    7.5K
 * Total Submissions: 18K
 * Testcase Example:  '["1","3","5","7"]\n100'
 *
 * 给定一个按 非递减顺序 排列的数字数组 digits 。你可以用任意次数 digits[i] 来写的数字。例如，如果 digits =
 * ['1','3','5']，我们可以写数字，如 '13', '551', 和 '1351315'。
 *
 * 返回 可以生成的小于或等于给定整数 n 的正整数的个数 。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：digits = ["1","3","5","7"], n = 100
 * 输出：20
 * 解释：
 * 可写出的 20 个数字是：
 * 1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75,
 * 77.
 *
 *
 * 示例 2：
 *
 *
 * 输入：digits = ["1","4","9"], n = 1000000000
 * 输出：29523
 * 解释：
 * 我们可以写 3 个一位数字，9 个两位数字，27 个三位数字，
 * 81 个四位数字，243 个五位数字，729 个六位数字，
 * 2187 个七位数字，6561 个八位数字和 19683 个九位数字。
 * 总共，可以使用D中的数字写出 29523 个整数。
 *
 * 示例 3:
 *
 *
 * 输入：digits = ["7"], n = 8
 * 输出：1
 *
 *
 *
 *
 * 提示：
 *
 *
 *
 * 1 <= digits.length <= 9
 * digits[i].length == 1
 * digits[i] 是从 '1' 到 '9' 的数
 * digits 中的所有值都 不同 
 * digits 按 非递减顺序 排列
 * 1 <= n <= 10^9
 *
 *
 */

// @lc code=start
class Solution
{
public:
    int dfs(const vector<int> &dig2, const vector<int> &dig, int digit)
    {
        if (digit < 0)
            return 1;
        int num = 0;
        for (auto &i : dig2)
        {
            if (i < dig[digit])
                num += pow(dig2.size(), digit);
            else if (i == dig[digit])
                num += dfs(dig2, dig, digit - 1);
            else
                return num;
        }
        return num;
    }

    int atMostNGivenDigitSet(vector<string> &digits, int n)
    {
        vector<int> dig;
        while (n)
        {
            dig.push_back(n % 10);
            n /= 10;
        }
        int digCnt = dig.size();
        n = digits.size();
        int ans = 0;
        vector<int> dig2(n, 0);
        for (int i = 0; i < n; i++)
            dig2[i] = digits[i][0] - '0';
        int i = 1;
        for (int j = 1; j < digCnt; j++)
        {
            i *= n;
            ans += i;
        }
        return dfs(dig2, dig, digCnt - 1) + ans;
    }
};
// @lc code=end
