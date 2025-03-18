#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*
 * @lc app=leetcode.cn id=670 lang=cpp
 *
 * [670] 最大交换
 */

// @lc code=start
class Solution
{
public:
    int maximumSwap(int num)
    {
        vector<int> nums;
        while (num)
        {
            nums.push_back(num % 10);
            num /= 10;
        }
        int n = nums.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);

        sort(idx.begin(), idx.end(), [r = nums.data()](int &a, int &b)
             {
        if (r[a] > r[b])
            return true;
        if (r[a] == r[b])
            return a > b;
        else
            return false; });
        n--;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[idx[i]] > nums[n])
            {
                while (i< nums.size() && nums[idx[i + 1]] == nums[idx[i]])
                {
                    i++;
                }
                swap(nums[idx[i]], nums[n]);
                break;
            }
            else if (nums[idx[i]] == nums[n])
            {
                n--;
            }
        }

        for (int i = nums.size() - 1; i >= 0; i--)
        {
            num *= 10;
            num += nums[i];
        }
        return num;
    }
};
// @lc code=end
