#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1625 lang=cpp
 *
 * [1625] 执行操作后字典序最小的字符串
 *
 * https://leetcode.cn/problems/lexicographically-smallest-string-after-applying-operations/description/
 *
 * algorithms
 * Medium (55.28%)
 * Likes:    83
 * Dislikes: 0
 * Total Accepted:    10.9K
 * Total Submissions: 17K
 * Testcase Example:  '"5525"\n9\n2'
 *
 * 给你一个字符串 s 以及两个整数 a 和 b 。其中，字符串 s 的长度为偶数，且仅由数字 0 到 9 组成。
 *
 * 你可以在 s 上按任意顺序多次执行下面两个操作之一：
 *
 *
 * 累加：将  a 加到 s 中所有下标为奇数的元素上（下标从 0 开始）。数字一旦超过 9 就会变成 0，如此循环往复。例如，s = "3456" 且 a
 * = 5，则执行此操作后 s 变成 "3951"。
 * 轮转：将 s 向右轮转 b 位。例如，s = "3456" 且 b = 1，则执行此操作后 s 变成 "6345"。
 *
 *
 * 请你返回在 s 上执行上述操作任意次后可以得到的 字典序最小 的字符串。
 *
 * 如果两个字符串长度相同，那么字符串 a 字典序比字符串 b 小可以这样定义：在 a 和 b 出现不同的第一个位置上，字符串 a
 * 中的字符出现在字母表中的时间早于 b 中的对应字符。例如，"0158” 字典序比 "0190" 小，因为不同的第一个位置是在第三个字符，显然 '5'
 * 出现在 '9' 之前。
 *
 *
 *
 * 示例 1：
 *
 *
 * 输入：s = "5525", a = 9, b = 2
 * 输出："2050"
 * 解释：执行操作如下：
 * 初态："5525"
 * 轮转："2555"
 * 累加："2454"
 * 累加："2353"
 * 轮转："5323"
 * 累加："5222"
 * 累加："5121"
 * 轮转："2151"
 * 累加："2050"​​​​​​​​​​​​
 * 无法获得字典序小于 "2050" 的字符串。
 *
 *
 * 示例 2：
 *
 *
 * 输入：s = "74", a = 5, b = 1
 * 输出："24"
 * 解释：执行操作如下：
 * 初态："74"
 * 轮转："47"
 * 累加："42"
 * 轮转："24"​​​​​​​​​​​​
 * 无法获得字典序小于 "24" 的字符串。
 *
 *
 * 示例 3：
 *
 *
 * 输入：s = "0011", a = 4, b = 2
 * 输出："0011"
 * 解释：无法获得字典序小于 "0011" 的字符串。
 *
 *
 * 示例 4：
 *
 *
 * 输入：s = "43987654", a = 7, b = 3
 * 输出："00553311"
 *
 *
 *
 *
 * 提示：
 *
 *
 * 2
 * s.length 是偶数
 * s 仅由数字 0 到 9 组成
 * 1
 * 1
 *
 *
 */

// @lc code=start
class Solution
{
public:
    string findLexSmallestString(string s, int a, int b)
    {
        int n = s.size();
        vector<int> v(n);
        vector<int> cnts(n);
        int skip = (b + 1) % 2 + 1; // b奇数 -> 1 b偶数->2
        int cnt = 10 / gcd(a, 10);
        for (int i = 0; i < n; i++)
        {
            v[i] = s[i] - '0';
        }
        vector<int> q;
        int mini = 10;
        int gcdbn = gcd(b, n);
        bool divided = gcdbn == 1; // 是否最大公约数为1~~是否有余数~~
        for (int i = 0; i < n; i++)
        {
            if (b % 2? true : i % 2)
                for (int j = 1; j < cnt; j++)
                {
                    int temp = ((s[i] - '0') + a * j) % 10;
                    if (v[i] > temp)
                    {
                        v[i] = temp;
                        cnts[i] = j;
                        
                    }
                }
            if (divided? !(i % skip) : !(i % gcdbn))
            {
                if (v[i] < mini)
                {
                    mini = v[i];
                    q.clear();
                    q.push_back(i);
                }
                else if (v[i] == mini)
                {
                    q.push_back(i);
                }
            }
        }
        string ans = s;
        int m = q.size();
        for (int i = 0; i < m; i++)
        {
            int start = q[i];
            string temp = s;
            int add_start = a * cnts[start];
            int add_next = a * cnts[(start + 1) % n];
            for (int j = 0; j < n; j++)
            {
                if (j % 2)
                    temp[j] = (s[(j + start) % n] - '0' + add_next) % 10 + '0';
                else
                    temp[j] = (s[(j + start) % n] - '0' + add_start) % 10 + '0';
            }
            if (temp < ans)
            {
                ans = temp;
            }
        }
        return ans;
    }

    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
};
// @lc code=end
