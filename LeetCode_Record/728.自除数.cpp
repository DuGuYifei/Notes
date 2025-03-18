#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=728 lang=cpp
 *
 * [728] 自除数
 */

// @lc code=start
class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;
        for(int i = left;i<=right;i++)
        {
            int temp = i;
            bool isDiv = true;
            while(temp != 0)
            {
                int div = temp%10;
                if(div == 0)
                {
                    isDiv = false;
                    break;
                }
                if(i%div != 0)
                {
                    isDiv = false;
                    break;
                }
                temp /= 10;
            }
            if(isDiv)
                ans.push_back(i);
        }
        return ans;
    }
};
// @lc code=end

