#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int k = n - 1;
            for (int j = i + 1; j < k; j++)
            {

                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                while (nums[i] + nums[j] + nums[k] > 0 && k > j + 1)
                {
                    k--;
                }

                if (nums[i] + nums[j] + nums[k] == 0)
                {
                    res.emplace_back(vector{nums[i], nums[j], nums[k]});
                    //break;
                }
            }
        }
        return res;
        // sort(nums.begin(), nums.end());
        // vector<vector<int>> res;
        // int i = 0;
        // int k = nums.size() - 1;
        // int j1 = 1, j2 = nums.size() - 2;
        // while (i < k - 1)
        // {
        //     if (nums[i] > 0 || nums[k] < 0)
        //         return res;

        //     if (nums[i] + nums[k] >= 0)
        //     {
        //         for (j1 = j1>i?j1:i+1; j1 < k; j1++)
        //         {
        //             if (nums[j1] + nums[i] + nums[k] > 0)
        //             {
        //                 j1--;
        //                 break;
        //             }
        //             else if (nums[j1] == nums[j1 - 1] && j1 > i+1)
        //                 continue;
        //             else if (nums[j1] + nums[i] + nums[k] == 0)
        //                {

        //                     res.emplace_back(vector{ nums[i], nums[j1], nums[k] });
        //                }
        //         }
        //         k--;
        //         while (nums[k] == nums[k + 1])
        //         {
        //             if (k <= i + 2)
        //                 return res;
        //             k--;
        //         }
        //     }
        //     else if (nums[i] + nums[k] < 0)
        //     {
        //         for (j2 = j2<k?j2:k-1; j2 >= i; j2--)
        //         {
        //             if (nums[j2] + nums[i] + nums[k] > 0)
        //             {
        //                 j2++;
        //                 break;
        //             }
        //             else if (nums[j2] == nums[j2 + 1] && j2<k-1)
        //                 continue;
        //             else if (nums[j2] + nums[i] + nums[k] == 0)
        //                 res.emplace_back(vector{ nums[i], nums[j2], nums[k] });
        //         }
        //         i++;
        //         while( nums[i] == nums[i - 1])
        //         {
        //             if (i >= k - 2)
        //                 return res;
        //             i++;
        //         }
        //     }
        // }
        //return res;
    }
};
// @lc code=end
