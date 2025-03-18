#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=735 lang=cpp
 *
 * [735] 行星碰撞
 */

// @lc code=start
class Solution
{
public:
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        vector<int> st;
        for (auto &i : asteroids)
        {
            bool nextFlag = false;
            while (i < 0 && !st.empty() && st.back() > 0)
            {
                if (st.back() >= -i)
                {
                    nextFlag = true;
                    if(st.back() == -i)
                        st.pop_back();
                    break;
                }
                st.pop_back();
            }
            if (nextFlag)
                continue;
            st.push_back(i);
        }
        return st;
    }
};
// @lc code=end
