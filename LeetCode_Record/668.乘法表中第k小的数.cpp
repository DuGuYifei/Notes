/*
1   2   3   4   5   6   7   8   9
2   4   6   8   10  12  14  16  28
3   6   9   12  15  18  21  24  27
4   8   12  16  20  24  28  32  36
5   10  15  20  25  30  35  40  45
6   12  18  24  30  36  42  48  54
7   14  21  28  35  42  49  56  63
8   16  24  32  40  48  56  64  72
9   18  27  36  45  54  63  72  81
*/

//求表中有几个数比x小
//将每行(i-th 行)比它小的相加 求和：∑min(x/i,n)
// i <= x/n => x/i >= n
// x/n * n + x/i(i:(x/n+1 : m))

/*
 * @lc app=leetcode.cn id=668 lang=cpp
 *
 * [668] 乘法表中第k小的数
 */

// @lc code=start
class Solution
{
public:
    int findKthNumber(int m, int n, int k)
    {
        //二分法
        int left = 1;
        int right = m * n;
        int num;
        //不能用 while(num !=k) 因为会算上自己（<=自己的数有多少个，而第k小不包含所有的自己，因此num有可能永远大于k）
        //也不能通过给每一行减1来达到效果，因为不是每行都有这个数字
        while (left<right)
        {
            int mid = (left + right) / 2;

            num = mid / n * n;
            for (int i = mid / n + 1; i <= m; i++)
            {
                num += mid / i;
            }
            if (num >= k)
                right = mid;
            else if (num < k)
                left = mid + 1;
        }
        return right;
    }
};
// @lc code=end
