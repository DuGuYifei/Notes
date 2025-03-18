#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1447 lang=cpp
 *
 * [1447] 最简分数
 */

// @lc code=start
class Solution
{
public:
    vector<string> simplifiedFractions(int n)
    {
        vector<string> ans;
        while (n > 1)
        {
            ans.push_back("1/" + to_string(n));
            int i = 2;
            while (i < n)
            {
                if (gcd(n,i)==1)
                {
                    ans.push_back(toStr(i) + "/" + toStr(n));
                }
                i++;
            }
            n--;
        }
        return ans;
    }

    int gcd(int a, int b)
    {
        if(b == 0) return a;
        return gcd(b, a%b);
    }

    string toStr(int n)
    {
        if(n==100)
            return "100";
        string s = "";
        if(n>=10)
        {   
            s.append(1, n/10+'0');
            n = n%10;
        }        
            s.append(1,n+'0');
        return s;
    }
};
// @lc code=end
