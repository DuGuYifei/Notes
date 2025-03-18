#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=798 lang=cpp
 *
 * [798] 得分最高的最小轮调
 */

// @lc code=start
class Solution
{
public:
    int bestRotation(vector<int> &nums)
    {
        // 每一个索引作为k时的分数
        int n = nums.size();
        vector<int>diff(n,0); // 记录第i次旋转造成结果产生什么变化

        // nums[i] <= i
        // index  012345   012345   012345  012345
        // origin xxxx2x   xxxxx0   x1xxxx  xxxxx5
        // score  111001   111111   101111  100000
        //        ^  ^ ^   ^        ^^^     ^^
        // k = 0; -1分：k = i - nums[i] + 1; +1分：k = i + 1

        // nums[i] > i
        // index  012345   012345
        // origin xx4xxx   xxxx5x
        // score  000110   111110
        //           ^ ^   ^    ^
        // k = 0; +1分：k = i + 1; -1分：k = i + 1 + n - nums[i]


        for (int i = 0; i < n; i++)
        {
            if(nums[i] <= i && nums[i] != n-1)
            {
                diff[0]++;
            }

            diff[(i + 1)%n]++;
            // if(nums[i] <= i)
            // {
            //     diff[i - nums[i] + 1]--;
            // }
            // else
            // {
                diff[(i + 1 + n - nums[i])%n]--;
            //}
        }
        int score = 0;
        int maxScore = 0;
        int ans = -1;
        for(int k = 0; k < n; k++)
        {
            score += diff[k];
            if(score > maxScore)
            {
                ans = k;
                maxScore = score;
            }
        }
        return ans;
    }
};
// @lc code=end
