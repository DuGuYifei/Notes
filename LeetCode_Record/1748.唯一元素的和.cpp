#include <vector>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=1748 lang=cpp
 *
 * [1748] 唯一元素的和
 */

// @lc code=start
// class Solution
// {
// public:
//     int sumOfUnique(vector<int> &nums)
//     {
//         unordered_map<int, int> n;
//         for (const int &i : nums)
//         {
//             n[i]++;
//         }
//         int sum = 0;
//         for (auto &[i1, i2] : n)
//         {
//             if (i2 == 1)
//                 sum += i1;
//         }
//         return sum;
//     }
// };
class Solution {
    public:
    int sumOfUnique(vector<int> &nums) {
        int count[101]= {0};
        for (int num : nums) count[num]++;
        int res = 0;
        for (int i = 1; i < 101; i++) {
            if (count[i] == 1) res += i;
        }
        return res;
    }
};
// @lc code=end
