#include <vector> 
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=946 lang=cpp
 *
 * [946] 验证栈序列
 */

// @lc code=start
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        for(int i = 0, j = 0;i < pushed.size(); i ++)
        {
            st.push(pushed[i]);
            while(!st.empty() && st.top() == popped[j])
            {
                st.pop();
                j++;
            }
        }
        return st.empty();
    }
};
// @lc code=end

