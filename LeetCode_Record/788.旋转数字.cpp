/*
 * @lc app=leetcode.cn id=788 lang=cpp
 *
 * [788] 旋转数字
 */

// @lc code=start
class Solution {
public:
    int rotatedDigits(int n) {
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            int test = i;
            bool isGood = false;
            while(test)
            {
                int t = test % 10;
                if(t == 2 || t == 5 || t == 6 || t == 9)
                {
                    isGood = true;
                }
                else if(t != 1 && t != 0 && t != 8)
                {
                    isGood = false;
                    break;
                }
                test/=10;
            }
            if(isGood)
                ans++;
        }
        return ans;
    }
};
// @lc code=end

