#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=2024 lang=cpp
 *
 * [2024] 考试的最大困扰度
 */

// @lc code=start
class Solution {
public:
    // 窗口右边增大，太大了就缩短左边
    int maxOfOneanswer(string& answerKey, int k, char tf)
    {
        int ans = 0;
        for(int left = 0, right = 0, sum = 0; right < answerKey.size(); right++)
        {
            sum += answerKey[right] != tf;
            while(sum>k)
            {
                sum -= answerKey[left++] != tf;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }

    int maxConsecutiveAnswers(string answerKey, int k) {
        return max(maxOfOneanswer(answerKey,k,'T'), maxOfOneanswer(answerKey,k,'F'));
    }
};
// @lc code=end

