#include <string>
#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=1656 lang=cpp
 *
 * [1656] 设计有序流
 */

// @lc code=start
class OrderedStream {
private:
    vector<string> stream;
    int ptr = 1;
public:

    OrderedStream(int n) {
        stream.resize(n+1);
    }
    
    vector<string> insert(int idKey, string value) {
        stream[idKey] = value;
        vector<string>ans;
        while(ptr < stream.size()  && !stream[ptr].empty())
        {
            ans.push_back(stream[ptr]);
            ptr++;
        }
        return ans;
    }
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
// @lc code=end

