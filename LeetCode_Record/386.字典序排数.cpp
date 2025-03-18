#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=386 lang=cpp
 *
 * [386] 字典序排数
 */

// @lc code=start
class Solution
{
public:
    vector<int> ans;
    int n;
    vector<int> lexicalOrder(int n)
    {
        this->n = n;
        nextLevel(1);
        return ans;
    }

    void nextLevel(int x)
    {
        if(x <= n)
            ans.push_back(x);
        else
            return;
        nextLevel(x*10);
        if(x%10 == 9)
            return;
        nextLevel(++x);
    }
    // vector<int> lexicalOrder(int n) {
    //     vector<int> ret(n);
    //     int number = 1;
    //     for (int i = 0; i < n; i++) {
    //         ret[i] = number;
    //         if (number * 10 <= n) {
    //             number *= 10;
    //         } else {
    //             while (number % 10 == 9 || number + 1 > n) {
    //                 number /= 10;
    //             }
    //             number++;
    //         }
    //     }
    //     return ret;
    // }
};

// @lc code=end
