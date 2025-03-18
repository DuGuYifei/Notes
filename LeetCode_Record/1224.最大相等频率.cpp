#include <unordered_map>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1224 lang=cpp
 *
 * [1224] 最大相等频率
 */

// @lc code=start
class Solution
{
public:
    int maxEqualFreq(vector<int> &nums)
    {
        unordered_map<int, int> freq, count;
        int ans = 0;
        int kindNum = 0;
        int maxFreq = 0;
        int s = nums.size();
        for (int i = 0; i < s; i++)
        {
            int n = freq[nums[i]];
            if (n == 0)
            {
                if(count[maxFreq] == kindNum)
                    ans = i + 1;
                kindNum++;
            }
            else
                count[n]--;
            maxFreq = max(++freq[nums[i]], maxFreq);
            count[freq[nums[i]]]++;
            if (count[freq[nums[i]]] == kindNum - 1 && (maxFreq == freq[nums[i]] + 1 || count[1] == 1)|| count[n] == kindNum - 1)
                ans = i + 1;
        }
        return ans;
    }
};
// @lc code=end
