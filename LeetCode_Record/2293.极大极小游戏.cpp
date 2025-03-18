#include <vector>
using namespace std;

class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        int n = nums.size();
        while(n > 1){
            for(int i = 0; i < n/2; i++){
                if(i % 2)
                    nums[i] = max(nums[i * 2], nums[i * 2 + 1]);
                else
                    nums[i] = min(nums[i * 2], nums[i * 2 + 1]);
            }
            n /= 2;
        }
        return nums[0];
    }
};