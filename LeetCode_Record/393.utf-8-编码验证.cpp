#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=393 lang=cpp
 *
 * [393] UTF-8 编码验证
 */

// @lc code=start
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int n = data.size();
        for(int i = 0; i< data.size();i++)
        {
            int t = data[i];
            if(t >> 7 == 0)
                continue;
            // 四个字节
            if(t >> 3 == 30)
            {
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                continue;
            }
            // 三个字节
            if(t>>4 == 14)
            {
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                continue;
            }
            // 两个字节
            if(t >> 5 == 6)
            {
                i++;
                if(i >= n) return false;
                if(data[i] >> 6 != 2)
                    return false;
                continue;
            }
            return false;
        }
        return true;
    }
};
// @lc code=end

