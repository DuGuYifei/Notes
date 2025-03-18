#include <vector>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=658 lang=cpp
 *
 * [658] 找到 K 个最接近的元素
 */

// @lc code=start
class Solution
{
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x)
    {
        // sort(arr.begin(), arr.end(), [x](int a, int b) -> bool
        //      { return abs(a - x) < abs(b - x) || abs(a - x) == abs(b - x) && a < b; });
        // sort(arr.begin(), arr.begin() + k);
        // return vector<int>(arr.begin(), arr.begin() + k);

        int right = lower_bound(arr.begin(), arr.end(),x) - arr.begin(); // 第一个大于或等于x的索引
        int left = right - 1;
        // 使用k--不是--k是因为判定k次，每次判定当前的数字
        // 正好最后返回 + left + 1 不包含 left，+ right 不包含 right
        while(k--)
        {
            if(right > arr.size())
                left--;
            else if(left < 0)
                right++;
            else if(arr[right] - x < x - arr[left])
                right++;
            else
                left--;
        }
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
};
// @lc code=end
