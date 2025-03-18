#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1652 lang=cpp
 *
 * [1652] 拆炸弹
 */

// @lc code=start
class Solution
{
public:
    vector<int> decrypt(vector<int> &code, int k)
    {
        int n = code.size();
        vector<int> ans(n, 0);
        if (k == 0)
        {
            return ans;
        }
        if(k > 0)
        {
            int j = 1;
            int sum = 0;
            for(int i = 0; i < k; i++)
            {
                if(j == n)
                    j = 0;
                sum += code[j++];
            }
            ans[0] = sum;
            for(int i = 1; i < n; i++)
            {

                sum-=code[i];
                if(j == n)
                    j = 0;
                sum += code[j++];
                ans[i] = sum;
            }
            return ans;
        }
        int j = n - 1;
        int sum = 0;
        k = -k;
        for(int i = 0; i < k; i++)
        {
            if(!~j)
            {
                j = n - 1;
            }
            sum += code[j--];
        }
        j++;
        ans[0] = sum;
        for(int i = 1; i < n; i++)
        {
            sum += code[i-1];
            if(j == n)
                j = 0;
            sum -= code[j++];
            ans[i] = sum;
        }
        return ans;
    }
};
// @lc code=end
