#include <vector>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=927 lang=cpp
 *
 * [927] 三等分
 */

// @lc code=start
class Solution
{
public:
    vector<int> threeEqualParts(vector<int> &arr)
    {
        //方法二：正确
        int n = arr.size();
        int cnt = 0;
        for (auto& i : arr)
        {
            if (i)
                cnt++;
        }
        if (!cnt)
            return { 0,2 };
        if (cnt % 3)
            return { -1,-1 };
        int cnt1 = cnt / 3;
        int cnt2 = cnt1 + cnt1;
        int cnt3 = cnt;
        int p1 = 0, p2 = 0, p3 = 0;
        cnt = 0;
        int zero = 0;
        int ansi = 0, ansj = 0;
        int i = 0;
        for (; i < n; i++)
        {
            if (arr[i])
                cnt++;
            if (cnt == cnt1)
            {
                p1 = i++;
                break;
            }
        }
        for (; i < n; i++)
        {
            if (arr[i])
                cnt++;
            if (cnt == cnt2)
            {
                p2 = i++;
                break;
            }
        }
        for (; i < n; i++)
        {
            if (arr[i])
                cnt++;
            if (cnt == cnt3)
            {
                int zero = n - i - 1;
                p3 = n-1;
                p1 += zero;
                ansi = p1;
                p2 += zero;
                ansj = p2 + zero + 1;
                break;
            }
        }   

        while (cnt1 > 0)
        {
            if (arr[p1] != arr[p2--] || arr[p1] != arr[p3--])
                return { -1,-1 };
            if (arr[p1--])
                cnt1--;
        }   

        return { ansi, ansj};


        //方法1：错误，会overflow，数字太大了
        // int n = arr.size() - 1;
        // int i = 0, j = n;
        // int p1 = arr[0], p2 = 0, p3 = arr[n];
        // for (int k = 1; k < n; k++)
        // {
        //     p2 = p2 * 2 + arr[k];
        // }
        // // 0, i | i+1, j-1 | j, n-1
        // while (i + 1 < j)
        // {
        //     if (p1 > p2 || p3 > p2)
        //         return {-1, -1};
        //     if (p1 > p3)
        //     {
        //         j--;
        //         p3 += arr[j] * pow(2, n - j);
        //         p2 /= 2;
        //     }
        //     else if (p1 < p3)
        //     {
        //         i++;
        //         p1 = p1 * 2 + arr[i];
        //         p2 -= arr[i] * pow(2, j - i - 1);
        //     }
        //     else
        //     {
        //         if (p1 == p2)
        //             return {i, j};
        //         j--;
        //         p2 /= 2;
        //         p3 += arr[j] * pow(2, n - j);

        //         if (arr[j])
        //         {
        //             i++;
        //             p1 = p1 * 2 + arr[i];
        //             p2 -= arr[i] * pow(2, j - i - 1);
        //         }
        //     }
        // }
        // return {-1, -1};
    }
};
// @lc code=end
