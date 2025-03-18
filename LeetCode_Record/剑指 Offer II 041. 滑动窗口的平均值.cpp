#include <queue>
using namespace std;
class MovingAverage {
private:
    int size;
    double sum;
    queue<int> que;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        this->size = size;
    }
    
    double next(int val) {
        if(que.size() == size)
        {
            sum -= que.front();
            que.pop();
        }
        que.push(val);
        sum += val;
        return sum/que.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */