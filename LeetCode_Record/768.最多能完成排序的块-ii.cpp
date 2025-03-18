#include <vector>
#include <stack>
using namespace std;
/*
 * @lc app=leetcode.cn id=768 lang=cpp
 *
 * [768] 最多能完成排序的块 II
 */

// @lc code=start
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> block;
        
        for(int& i:arr)
        {
            if(block.empty() || i >= block.top())
            {
                block.push(i);
            }
            else
            {
                int maxn = block.top();
                block.pop();
                //找到跟 i 一组的下限，下限再往前一组可以一样的值，这样就可以多出一组
                //已经保证了下面都是排序好的
                while(!block.empty() && block.top() > i)
                {
                    block.pop();
                }
                //这一组只留下maxn，最大值
                block.push(maxn);
            }
        }
        return block.size();   
    }
};
// @lc code=end

