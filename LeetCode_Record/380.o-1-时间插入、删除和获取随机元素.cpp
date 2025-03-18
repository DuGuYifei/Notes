#include <vector>
#include <unordered_map>
#include <time.h>
using namespace std;
/*
 * @lc app=leetcode.cn id=380 lang=cpp
 *
 * [380] O(1) 时间插入、删除和获取随机元素
 */

// @lc code=start
class RandomizedSet {
private:
    vector<int> nums;
    int size = 0;
    unordered_map<int, int> indexes;
public:
    RandomizedSet() {
        //srand((unsigned)time(NULL));
    }
    
    bool insert(int val) {
        if(indexes[val] != 0)
            return false;
        if(indexes[val] == 0 && size > 0 && nums[0] == val)
        {
            return false;
        }
        nums.push_back(val);
        indexes[val] = size;
        size++;
        return true;
    }
    
    bool remove(int val) {
        if(indexes[val] == 0 && (size == 0 || nums[0] != val))
        {
            return false;
        }
        int index = indexes[val];
        int last = nums[size - 1];
        nums[index] = last;
        indexes[last] = index;
        indexes[val] = 0;
        nums.pop_back();
        size--;
        return true;
    }
    
    int getRandom() {
        return nums[rand() % size];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
// @lc code=end

