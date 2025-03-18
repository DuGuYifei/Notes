#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=373 lang=cpp
 *
 * [373] 查找和最小的K对数字
 */

// @lc code=start
class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {
        int index1 = 0, index2 = 0;
        int size1 = nums1.size() - 1;
        int size2 = nums2.size() - 1;
        vector<vector<int>> res = {{nums1[0], nums2[0]}};
        for (int i = 1; i < k; i++)
        {
            if (index1 == index2)
            {
                if (index1 == size1)
                {
                    res.emplace_back(vector<int>{nums1[index1], nums2[++index2]});
                }
                else if (index2 == size2)
                {
                    res.emplace_back(vector<int>{nums1[++index1], nums2[index2]});
                }
                else
                {
                    nums1[index1] + nums2[index2 + 1] < nums1[index1 + 1] + nums2[index2] ? res.emplace_back(vector<int>{nums1[index1], nums2[++index2]}) : res.emplace_back(vector<int>{nums1[++index1], nums2[index2]});
                }
            }
            else if (index1 > index2)
            {
                if (index1 == size1)
                {
                    res.emplace_back(vector<int>{nums1[--index1], nums2[++index2]});
                }
                else if (index2 == size2)
                {
                    res.emplace_back(vector<int>{nums1[++index1], nums2[index2]});
                }
                else
                {
                    nums1[index1 + 1] + nums2[index2] < nums1[index1 - 1] + nums2[index2 + 1] ? res.emplace_back(vector<int>{nums1[++index1], nums2[index2]}) : res.emplace_back(vector<int>{nums1[--index1], nums2[++index2]});
                }
            }
            else if (index2 > index1)
            {
                if (index1 == size1)
                {
                    res.emplace_back(vector<int>{nums1[index1], nums2[++index2]});
                }
                else if (index2 == size2)
                {
                    res.emplace_back(vector<int>{nums1[++index1], nums2[--index2]});
                }
                else
                {
                    nums1[index1] + nums2[index2 + 1] < nums1[index1 + 1] + nums2[index2 - 1] ? res.emplace_back(vector<int>{nums1[index1], nums2[++index2]}) : res.emplace_back(vector<int>{nums1[++index1], nums2[--index2]});
                }
            }
            if (index1 == size1 && index2 == size2)
                break;
        }
        return res;
    }
};
// @lc code=end
