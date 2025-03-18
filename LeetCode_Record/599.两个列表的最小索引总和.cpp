#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
/*
 * @lc app=leetcode.cn id=599 lang=cpp
 *
 * [599] 两个列表的最小索引总和
 */

// @lc code=start
class Solution
{
public:
    vector<string> findRestaurant(vector<string> &list1, vector<string> &list2)
    {
        vector<string> ans;
        int sum = 2001;
        unordered_map<string, int> restaurant;
        int index = 0;
        for (string &i : list1)
        {
            restaurant[i] = index + 1;
            index++;
        }
        index = 0;
        for (string &i : list2)
        {
            int temp = restaurant[i];
            if (temp != 0)
            {
                temp += index;
                if (temp < sum)
                {
                    ans = vector<string>{i};
                    sum = temp;
                }
                else if (temp == sum)
                {
                    ans.push_back(i);
                }
            }
            index++;
        }
        return ans;
    }
};
// @lc code=end
