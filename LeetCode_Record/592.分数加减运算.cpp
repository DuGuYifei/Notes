#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=592 lang=cpp
 *
 * [592] 分数加减运算
 */

// @lc code=start
class Solution
{
public:
    string fractionAddition(string expression)
    {
        int n = expression.size();
        int index = 0;
        long long deno = 0, nume = 1;
        while (index < n)
        {
            long long denominator = 0, sign = 1, numerator = 0;
            if (expression[index] == '-')
            {
                sign = -1;
                index ++;
            }
            else if (expression[index] == '+')
            {
                index ++;
            }
            while(index<n && expression[index] != '/')
            {
                denominator = denominator * 10 + expression[index] - '0';
                index++;
            }
            index++;
            while(index<n && expression[index] != '+' && expression[index] != '-')
            {
                numerator = numerator * 10 + expression[index] - '0';
                index++;
            }
            deno = deno * numerator + denominator * nume * sign;
            nume *= numerator;
        }
        if(deno == 0)
            return "0/1";
        long long g = gcd(abs(deno), nume);
        return to_string(deno/g) + '/' + to_string(nume/g);
    }

    int gcd(long long a, long long b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
};
// @lc code=end
