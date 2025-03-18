#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
/*
 * @lc app=leetcode.cn id=954 lang=cpp
 *
 * [954] 二倍数对数组
 */

// @lc code=start
class Solution {
public:
    bool canReorderDoubled(vector<int>& arr) {
        unordered_map<int, int> stat;
        for(int&i:arr)
        {
            stat[i]++;
        }
        // 如果有0元素，则必须是偶数，因为0*2=0
        if(stat[0] % 2)
            return false;
        // 关键，按照·绝对值·排序
        vector<int>key;
        key.reserve(stat.size());
        for(auto& [a,b] : stat)
        {
            key.push_back(a);
        }
        sort(key.begin(),key.end(),[](int a, int b){return abs(a)<abs(b);});
        for(int& i:key)
        {
            // 这里不是相同数量，因为，第二个数也可以做第一个数
            if(stat[i] > stat[i*2])
            {
                return false;
            }
            stat[i*2]-=stat[i];
        }
        return true;
    }
};
// @lc code=end

