#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=816 lang=cpp
 *
 * [816] 模糊坐标
 *
 * https://leetcode-cn.com/problems/ambiguous-coordinates/description/
 *
 * algorithms
 * Medium (51.45%)
 * Likes:    52
 * Dislikes: 0
 * Total Accepted:    6.1K
 * Total Submissions: 11.6K
 * Testcase Example:  '"(123)"'
 *
 * 我们有一些二维坐标，如 "(1, 3)" 或 "(2,
 * 0.5)"，然后我们移除所有逗号，小数点和空格，得到一个字符串S。返回所有可能的原始字符串到一个列表中。
 * 
 * 原始的坐标表示法不会存在多余的零，所以不会出现类似于"00", "0.0", "0.00", "1.0", "001",
 * "00.01"或一些其他更小的数来表示坐标。此外，一个小数点前至少存在一个数，所以也不会出现“.1”形式的数字。
 * 
 * 最后返回的列表可以是任意顺序的。而且注意返回的两个数字中间（逗号之后）都有一个空格。
 * 
 * 
 * 
 * 
 * 示例 1:
 * 输入: "(123)"
 * 输出: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]
 * 
 * 
 * 
 * 示例 2:
 * 输入: "(00011)"
 * 输出:  ["(0.001, 1)", "(0, 0.011)"]
 * 解释: 
 * 0.0, 00, 0001 或 00.01 是不被允许的。
 * 
 * 
 * 
 * 示例 3:
 * 输入: "(0123)"
 * 输出: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)",
 * "(0.12, 3)"]
 * 
 * 
 * 
 * 示例 4:
 * 输入: "(100)"
 * 输出: [(10, 0)]
 * 解释: 
 * 1.0 是不被允许的。
 * 
 * 
 * 
 * 
 * 提示: 
 * 
 * 
 * 4 <= S.length <= 12.
 * S[0] = "(", S[S.length - 1] = ")", 且字符串 S 中的其他元素都是数字。
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
        vector<string> ambiguousCoordinates(string s) {
        int n = s.size() - 1;
        vector<string> ans;
        int id = 1;
        if(s[1] == '0')
        {
            vector<string> right = addDot(s.substr(2, n - 2));
            for(auto& i : right)
                ans.push_back("(0, " + i + ")");
            while(s[id] == '0')
                id++;
            if(n > 4 && id == n)
                return {};
        }
        string l = s.substr(1, id);
        id++;
        for(; id < n; id++)
        {
            vector<string> left = addDot(l);
            vector<string> right = addDot(s.substr(id, n - id));

            for(auto& i : left)
                for(auto& j : right)
                    ans.push_back("(" + i + ", " + j + ")");

            l.push_back(s[id]);
        }
        return ans;
    }

    vector<string> addDot(const string& num){
        int n = num.size();
        if(num.back() == '0') 
        {
            if(n == 1 || num[0] != '0')
                return { num };
            if(num[0] == '0')
                return {};
        }
        if(num[0] == '0')
            return { "0." + num.substr(1) };
        vector<string> res;
        for(int i = 1; i < n; i++)
            res.push_back(num.substr(0, i) + "." + num.substr(i));
        res.push_back(num);
        return res;
    }
};
// @lc code=end

