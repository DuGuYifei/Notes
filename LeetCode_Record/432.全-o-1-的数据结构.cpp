#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
/*
 * @lc app=leetcode.cn id=432 lang=cpp
 *
 * [432] 全 O(1) 的数据结构
 */

// @lc code=start
class AllOne {
    unordered_map<string, int> all;
    priority_queue<pair<int ,string>> maxPile;
    priority_queue<pair<int ,string>, vector<pair<int ,string>>, greater<>>minPile;
public:
    AllOne() {

    }
    
    void inc(string key) {
        all[key]++;
        maxPile.emplace(all[key],key);
        minPile.emplace(all[key],key);
    }
    
    void dec(string key) {
        all[key]--;
        if(all[key]==0)
        {
            all.erase(key);
            return;
        }
        maxPile.emplace(all[key],key);
        minPile.emplace(all[key],key);
    }
    
    string getMaxKey() {
        while(!maxPile.empty())
        {
            if(maxPile.top().first != all[maxPile.top().second])
                maxPile.pop();
            else
                return maxPile.top().second;
        }
        return "";
    }
    
    string getMinKey() {
        while(!minPile.empty())
        {
            if(minPile.top().first != all[minPile.top().second])
                minPile.pop();
            else
                return minPile.top().second;
        }
        return "";
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
// @lc code=end

