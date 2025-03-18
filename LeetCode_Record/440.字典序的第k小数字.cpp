/*
 * @lc app=leetcode.cn id=440 lang=cpp
 *
 * [440] 字典序的第K小数字
 */

// @lc code=start
class Solution
{
public:
    // 遍历字典序每个数字，太慢了，会超时，用方法二
    // int currIndex = 0;
    // int cur = 0;
    // int nth;
    // int n;
    // bool nextLevel(long start)
    // {
    //     if (start > n)
    //         return false;
    //     currIndex++;
    //     if (currIndex == nth)
    //     {
    //         cur = start;
    //         return true;
    //     }
    //     if (start == n)
    //     {
    //         return false;
    //     }
    //     if (nextLevel(start * 10))
    //         return true;
    //     for (int i = 1; i <= 9; i++)
    //     {
    //         start++;
    //         currIndex++;
    //         if (currIndex == nth)
    //         {
    //             cur = start;
    //             return true;
    //         }
    //         if (start == n)
    //         {
    //             return false;
    //         }
    //         if(nextLevel(start*10))
    //             return true;
    //     }
    //     return false;
    // }
    // int findKthNumber(int nn, int k)
    // {
    //     n = nn;
    //     nth = k;
    //     nextLevel(1);
    //     return cur;
    // }

    //-------- 方法二-------------
    //直接一行一行跳过，检测在哪个部分，
    //再在该部分的第一行子树下用同样的方法得到在哪个部分
    //以此类推，最终得到在哪

    int rowNum(int curr, long n)
    {
        long first = curr;
        long last = curr;
        int num = 0;
        while(first <= n)
        {
            num += min(last, n) - first + 1;
            first = first * 10;
            last = last * 10 + 9;
        }
        return num;
    }
    int findKthNumber(int n, int k)
    {
        int curr = 1;
        while(k>0)
        {
            int step = rowNum(curr , n);
            if(step < k)
            {
                k -= step;
                curr++; // 横向移动直接到下一个开头的数字
            }
            else{
                k--;
                if(k==0)
                    return curr;
                curr *= 10;
            }
        }
        return curr;
    }
};
// @lc code=end
