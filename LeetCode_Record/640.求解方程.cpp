#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=640 lang=cpp
 *
 * [640] 求解方程
 */

// @lc code=start
class Solution {
public:
    string solveEquation(string equation) {
        int index = 0;
        int sign = 1;
        int rate = 0;
        int rightNum = 0;
        char c;
        int num = 0;
        while(equation[index] != '=')
        {
            c = equation[index];
            if(c == '-')
                sign = -1;
            else if(c == '+')
                sign = 1;
            else if(c == 'x')
                rate += sign;
            else
            {
                num = 0;
                while(c != '+' && c != '-' && c != '=')
                {
                    if(c == 'x')
                    {
                        rate += num * sign;
                        break;
                    }
                    num = num * 10 + c - '0';
                    index++;
                    c = equation[index];
                }
                if(c != 'x')
                {
                    index--;
                    rightNum -= num * sign;
                }
            }
            index++;
        }
        index++;
        int n = equation.size();
        sign = 1;
        while(index < n)
        {
            c = equation[index];
            if(c == '-')
                sign = -1;
            else if(c == '+')
                sign = 1;
            else if(c == 'x')
                rate -= sign;
            else
            {
                num = 0;
                while(c != '+' && c != '-' && index < n)
                {
                    if(c == 'x')
                    {
                        rate -= num * sign;
                        break;
                    }
                    num = num * 10 + c - '0';
                    index++;
                    c = equation[index];
                }
                if(c != 'x')
                {
                    index--;
                    rightNum += num * sign;
                }
            }
            index++;
        }
        
        if(rate == 0)
            if(rightNum == 0)
                return "Infinite solutions";
            else
                return "No solution";
        return "x=" + to_string(rightNum/rate);
    }
};
// @lc code=end

