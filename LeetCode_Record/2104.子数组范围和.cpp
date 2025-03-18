#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=2104 lang=cpp
 *
 * [2104] 子数组范围和
 */

// @lc code=start
class Solution
{
public:
    long long subArrayRanges(vector<int> &nums)
    {
        // // 暴力枚举，双循环
        // int n = nums.size();
        // if(n == 1)
        //     return 0;
        // long long ans = 0;

        // for (int i = 0; i < n - 1; i++)
        // {
        //     int max = nums[i];
        //     int min = max;
        //     for (int j = i + 1; j < n; j++)
        //     {
        //         if (nums[j] > max)
        //             max = nums[j];
        //         if (nums[j] < min)
        //             min = nums[j];
        //         ans += (max - min);
        //     }
        // }
        // return ans;

        // 单调栈，原题可看作 max的和 - min的和
        int n = nums.size();
        long long ans = 0;
        vector<int> minLeft(n), maxLeft(n), minRight(n), maxRight(n);
        stack<int> minStack, maxStack;

        // 先弄左侧
        int i = 0;
        for (; i < n; i++)
        {
            //这里注意小于等于号，因为会一正一反两次遍历，所以两次必须遵从一样的选择一侧保留最大值等于，一侧保留最小值等于，或者相反，但是不能两侧都是最大或最小等于，因为会将窗口范围变大。
            // pop掉不用管前面的了，因为后面再比较这个（top）就已经是左边最大的了，或者更大的已经在它（top）右边了
            while (!maxStack.empty() && nums[maxStack.top()] <= nums[i])
            {
                maxStack.pop();
            }
            maxLeft[i] = (maxStack.empty() ? -1 : maxStack.top());
            maxStack.push(i);
            // 同理最小值
            while (!minStack.empty() && nums[minStack.top()] > nums[i])
            {
                minStack.pop();
            }
            minLeft[i] = (minStack.empty() ? -1 : minStack.top());
            minStack.push(i);
        }

        // 清空stack接着用
        maxStack = stack<int>();
        minStack = stack<int>();

        // 再弄右侧
        for (--i; i >-1; i--)
        {
            // pop掉不用管前面的了，因为后面再比较这个（top）就已经是右边最大的了，或者更大的已经在它（top）左边了
            while (!maxStack.empty() && nums[maxStack.top()] < nums[i])
            {
                maxStack.pop();
            }
            maxRight[i] = (maxStack.empty() ? n : maxStack.top());
            maxStack.push(i);
            // 同理最小值
            while (!minStack.empty() && nums[minStack.top()] >= nums[i])
            {
                minStack.pop();
            }
            minRight[i] = (minStack.empty() ? n : minStack.top());
            minStack.push(i);
        }

        for(int i = 0; i < n;i++)
        {
            ans += static_cast<long long>(i - maxLeft[i]) * (maxRight[i] - i) * nums[i] + static_cast<long long>(minLeft[i] - i) * (minRight[i] - i) * nums[i];
        }

        return ans;
    }
};
// @lc code=end 
