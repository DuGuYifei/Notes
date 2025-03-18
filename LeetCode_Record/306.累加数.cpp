#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=306 lang=cpp
 *
 * [306] 累加数
 */

// @lc code=start
class Solution
{
public:
    bool isAdditiveNumber(string num)
    {
        if (num == "000")
            return true;
        for (int i = 0; i < (num.size() - 1) / 2; i++)
        {
            for (int j = 0; j < ((num.size() - i) / 2 > i ? (num.size() - i) / 2 : (num.size() - 2 * i)); j++)
            {
                if (backPart(num, 0, i, i + 1, i + j + 1))
                    return true;
            }
        }
        return false;
    };

    bool backPart(string num, int abeg, int aend, int bbeg, int bend)
    {
        int cend = (aend - abeg > bend - bbeg? aend - abeg : bend - bbeg) + 1 + bend;
        
        if (bend == num.size() - 1)
            return true;

        if (cend < num.size())
        {
            if (cend == num.size() -  1)
            {
                return AddTest(num, abeg, aend, bbeg, bend, bend + 1, cend);
            }
            else
                return AddTest(num, abeg, aend, bbeg, bend, bend + 1, cend) && backPart(num, bbeg, bend, bend + 1, cend) || AddTest(num, abeg, aend, bbeg, bend, bend + 1, cend+1) && backPart(num, bbeg, bend, bend + 1, cend+1);
        }
        return false;
    }

    bool AddTest(string num, int abeg, int aend, int bbeg, int bend, int cbeg, int cend)
    {
        if (num[bbeg] == '0' && bend - bbeg > 0 || num[cbeg] == '0')
        {
            return false;
        }
        if (aend - abeg > bend - bbeg)
            return AddTest(num, bbeg, bend, abeg, aend, cbeg, cend);
        bool bit = 0;
        char med;
        while (aend != abeg - 1)
        {
            med = num[aend] + num[bend] - '0' + bit;
            if (med > '9')
            {
                bit = 1;
                med -= 10;
            }
            else
            {
                bit = 0;
            }

            if (med != num[cend])
                return false;
            cend--;
            aend--;
            bend--;
        }

        while (bend != bbeg - 1)
        {
            med = num[bend] + bit;
            if (med > '9')
            {
                bit = 1;
                med -= 10;
            }
            else
            {
                bit = 0;
            }
            if (med != num[cend])
                return false;

            cend--;
            bend--;
        }
        if (bit == 1)
            return num[cbeg] == '1';

        return true;
    }

    // string Add(string a, string b)
    // {

    //     int indexa = a.size(), indexb = b.size();
    //     if (indexb > indexa)
    //         return Add(b, a);
    //     a = '0' + a;
    //     indexa += 1;
    //     while (indexb != -1)
    //     {
    //         a[indexa] += b[indexb] - '0';
    //         if (a[indexa] > '9')
    //             a[indexa - 1] += 1;
    //         a[indexa] -= 10;

    //         indexa--;
    //         indexb--;
    //     }

    //     if(a[indexa] == '1')
    //         return a;
    //     else if(a[indexa] == ' ')
    //         return a.substr(1);
    //     while(indexa != 0)
    //     {
    //         if (a[indexa] > '9')
    //             a[indexa - 1] += 1;
    //         a[indexa] -= 10;
    //         indexa--;
    //     }
    //     if(a[0] == '1')
    //         return a;
    //     else if(a[0] == ' ')
    //         return a.substr(1);

    // }
};
// @lc code=end
