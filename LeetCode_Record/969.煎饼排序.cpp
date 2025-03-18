#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=969 lang=cpp
 *
 * [969] 煎饼排序
 */

// @lc code=start
class Solution
{
public:
    vector<int> pancakeSort(vector<int> &arr)
    {
        vector<int> ans;
        for (int i = arr.size(); i > 1; i--)
        {
            if (arr[i - 1] == i)
                continue;
            for (int j = 0; j < i - 1; j++)
            {
                if (arr[j] == i)
                {
                    if (j != 0)
                    {
                        reverse(arr.begin(), arr.begin() + j + 1);
                        ans.push_back(j + 1);
                    }
                    reverse(arr.begin(), arr.begin() + i);
                    ans.push_back(i);
                    break;
                }
            }
        }
        return ans;
    }
};
// @lc code=end
