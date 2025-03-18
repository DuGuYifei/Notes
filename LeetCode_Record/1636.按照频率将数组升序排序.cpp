#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1636 lang=cpp
 *
 * [1636] 按照频率将数组升序排序
 */

// @lc code=start
class Solution
{
public:
    vector<int> frequencySort(vector<int> &nums)
    {
        unordered_map<int, int> cnts;
        for (auto& i : nums)
            cnts[i]++;
        sort(nums.begin(),nums.end(), [&cnts](const int& a, const int& b){
            return cnts[a] != cnts[b]? cnts[a] < cnts[b]: a > b;
        });
        return nums;
    }
};
// @lc code=end
