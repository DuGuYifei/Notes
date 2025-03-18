#include <vector>
#include <limits.h>
using namespace std;
/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */

// @lc code=start
class Solution
{
public:
    // double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    // {
    //     int m = nums1.size(), n = nums2.size();

    //     if ((m + n) % 2 == 1)
    //         return getNthBigElement(nums1, nums2, (m + n + 1) / 2);
    //     else
    //         return (double)(getNthBigElement(nums1, nums2, (m + n) / 2) + getNthBigElement(nums1, nums2, (m + n) / 2 + 1)) / 2;

    // }

    // int getNthBigElement(const vector<int>& nums1, const vector<int>& nums2, int target)
    // {
    //     int half = 0, pos1 = 0, pos2 = 0, pivot1, pivot2;
    //     int m = nums1.size();
    //     int n = nums2.size();
    //     while (true)
    //     {

    //         if (pos1 >= nums1.size())
    //         {
    //             return nums2[pos2 + target - 1];
    //         }
    //         else if (pos2 >= nums2.size())
    //         {
    //             return nums1[pos1 + target - 1];
    //         }
    //         else if(target == 1)
    //             return min(nums1[pos1], nums2[pos2]);

    //         half = target / 2;
    //         pivot1 = min(pos1 + half, m) - 1;
    //         pivot2 = min(pos2 + half, n) - 1;

    //         if (nums1[pivot1] < nums2[pivot2])
    //         {
    //             target -= pivot1 - pos1 + 1;
    //             pos1 += half;

    //         }
    //         else
    //         {
    //             target -= pivot2 - pos2 + 1;
    //             pos2 += half;
    //         }
    //     }
    // }
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        if (m > n)
            return findMedianSortedArrays(nums2, nums1);

        int pivot1 = m / 2;
        int pivot2 = (m + n + 1) / 2 - pivot1;

        int medodd;
        int medeven;

        while (true)
        {

            int m1 = pivot1 <= 0 ? INT_MIN : nums1[pivot1 - 1];
            int m2 = pivot1 >= m ? INT_MAX : nums1[pivot1];
            int n1 = pivot2 <= 0 ? INT_MIN : nums2[pivot2 - 1];
            int n2 = pivot2 >= n ? INT_MAX : nums2[pivot2];

            if (m1 > n2)
            {
                pivot1 -= 1;
                pivot2 += 1;
            }
            else if (n1 > m2)
            {
                pivot1 += 1;
                pivot2 -= 1;
            }
            else
            {
                medodd = max(m1, n1);
                medeven = min(m2, n2);
                break;
            }
        }
        if ((m + n) % 2 == 1)
            return medodd;
        else
            return ((double)(medodd + medeven)) / 2;
    }
};
// @lc code=end
