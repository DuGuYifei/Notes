#include <string>
using namespace std;

/*
 * @lc app=leetcode.cn id=1106 lang=cpp
 *
 * [1106] 解析布尔表达式
 *
 * https://leetcode-cn.com/problems/parsing-a-boolean-expression/description/
 *
 * algorithms
 * Hard (58.49%)
 * Likes:    72
 * Dislikes: 0
 * Total Accepted:    6.2K
 * Total Submissions: 10.2K
 * Testcase Example:  '"&(|(f))"'
 *
 * 给你一个以字符串形式表述的 布尔表达式（boolean） expression，返回该式的运算结果。
 * 
 * 有效的表达式需遵循以下约定：
 * 
 * 
 * "t"，运算结果为 True
 * "f"，运算结果为 False
 * "!(expr)"，运算过程为对内部表达式 expr 进行逻辑 非的运算（NOT）
 * "&(expr1,expr2,...)"，运算过程为对 2 个或以上内部表达式 expr1, expr2, ... 进行逻辑 与的运算（AND）
 * "|(expr1,expr2,...)"，运算过程为对 2 个或以上内部表达式 expr1, expr2, ... 进行逻辑 或的运算（OR）
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 输入：expression = "!(f)"
 * 输出：true
 * 
 * 
 * 示例 2：
 * 
 * 输入：expression = "|(f,t)"
 * 输出：true
 * 
 * 
 * 示例 3：
 * 
 * 输入：expression = "&(t,f)"
 * 输出：false
 * 
 * 
 * 示例 4：
 * 
 * 输入：expression = "|(&(t,f,t),!(t))"
 * 输出：false
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= expression.length <= 20000
 * expression[i] 由 {'(', ')', '&', '|', '!', 't', 'f', ','} 中的字符组成。
 * expression 是以上述形式给出的有效表达式，表示一个布尔值。
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool parseBoolExpr(string expression) {
        bool ans = false;
        int i = 0;
        switch (expression[0])
        {
        case '!':
            i += 2;
            ans = notEx(expression, i);
            break;
        case '|':
            i += 2;
            ans = orEx(expression, i);
            break;
        case '&':
            i += 2;
            ans = andEx(expression, i);
            break;
        case 'f':
            return false;
        case 't':
            return true;
        default:
            break;
        }
        return ans;
    }

    bool notEx(const string& expression, int& i)
    {
        bool ans = false;

        switch (expression[i])
        {
        case '!':
            i += 2;
            ans = !notEx(expression, i);
            break;
        case '|':
            i += 2;
            ans = !orEx(expression, i);
            break;
        case '&':
            i += 2;
            ans = !andEx(expression, i);
            break;
        case 'f':
            ans = true;
            break;
        }

        i++;

        return ans;
    }   

    bool orEx(const string& expression, int& i)
    {
        bool ans = false;
        while(expression[i] != ')')
        {
            switch (expression[i])
            {
            case '!':
                i += 2;
                ans |= notEx(expression, i);
                break;
            case '|':
                i += 2;
                ans |= orEx(expression, i);
                break;
            case '&':
                i += 2;
                ans |= andEx(expression, i);
                break;
            case 't':
                ans = true;
                break;
            default:
                break;
            }
            i++;
            if(ans && expression[i] != ')')
                skip(expression, i);
        }
        return ans;
    }

    bool andEx(const string& expression, int& i)
    {
        bool ans = true;
        while(expression[i] != ')')
        {
            switch (expression[i])
            {
            case '!':
                i += 2;
                ans &= notEx(expression, i);
                break;
            case '|':
                i += 2;
                ans &= orEx(expression, i);
                break;
            case '&':
                i += 2;
                ans &= andEx(expression, i);
                break;
            case 'f':
                ans = false;
                break;
            default:
                break;
            }
            i++;
            if(!ans && expression[i] != ')')
                skip(expression, i);
        }
        return ans;
    }

    void skip(const string& expression, int& i)
    {
        int deep = 1;
        while(deep)
        {
            i++;
            if(expression[i] == '(')
                deep++;
            else if(expression[i] == ')')
                deep--;
        }
    }
};
// @lc code=end

