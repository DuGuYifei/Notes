#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=385 lang=cpp
 *
 * [385] 迷你语法分析器
 */
class NestedInteger
{
public:
    // Constructor initializes an empty nested list.
    NestedInteger();
    // Constructor initializes a single integer.
    NestedInteger(int value);
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;
    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;
    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);
    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};
// @lc code=start
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution
{
public:
    NestedInteger deserialize(string s)
    {
        if (s[0] != '[')
        {
            return stoi(s);
        }
        NestedInteger ans;
        string num = "";
        bool neg = false;
        int cnt = 1;
        // for (int i = 1; i < s.size(); i++)
        // {
        //     if (s[i] == ',')
        //     {
        //         if (cnt == 1 && num != "")
        //         {
        //             int t = stoi(num);
        //             if (neg)
        //             {
        //                 t *= -1;
        //                 neg = false;
        //             }
        //             ans.add(NestedInteger(t));
        //             num = "";
        //         }
        //     }
        //     else if (s[i] == '[')
        //     {
        //         cnt++;
        //         if (cnt == 2)
        //             ans.add(deserialize(s.substr(i)));
        //     }
        //     else if (s[i] == ']')
        //     {
        //         cnt--;
        //         if (cnt == 0)
        //         {
        //             if (num != "")
        //             {
        //                 int t = stoi(num);
        //                 if (neg)
        //                 {
        //                     t *= -1;
        //                     neg = false;
        //                 }
        //                 ans.add(NestedInteger(t));
        //             }
        //             break;
        //         }
        //     }
        //     else if (s[i] == '-')
        //     {
        //         if(cnt == 1)
        //             neg = true;
        //     }
        //     else
        //     {
        //         if (cnt == 1)
        //             num += s[i];
        //     }
        // }
        for (int i = 1; i < s.size(); i++)
        {
            if (cnt == 1)
            {
                if (s[i] == ',')
                {
                    if (num != "")
                    {
                        int t = stoi(num);
                        if (neg)
                        {
                            t *= -1;
                            neg = false;
                        }
                        ans.add(NestedInteger(t));
                        num = "";
                    }
                }
                else if (s[i] == '[')
                {
                    cnt++;
                    ans.add(deserialize(s.substr(i)));
                }
                else if (s[i] == ']')
                {
                    cnt--;
                    if (num != "")
                    {
                        int t = stoi(num);
                        if (neg)
                        {
                            t *= -1;
                            neg = false;
                        }
                        ans.add(NestedInteger(t));
                    }
                    break;
                }
                else if (s[i] == '-')
                {
                    neg = true;
                }
                else
                {
                    num += s[i];
                }
            }
            else
            {
                if(s[i] == '[')
                    cnt++;
                else if(s[i] == ']')
                    cnt--;
            }
        }
        return ans;
    }
};
// @lc code=end
