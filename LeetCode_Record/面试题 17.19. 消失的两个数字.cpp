#include<vector>
using namespace std;
class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        int xorsum = nums[0];
        int n = nums.size();
        for(int i = 1; i < n ; i++)
        {
            xorsum ^= nums[i];
            xorsum ^= i;
        }
        xorsum ^= n ^ (n+1) ^ (n+2); 

        int lsb = (xorsum == INT_MIN? xorsum : xorsum & (-xorsum));
        int type1 = 0, type2 = 0;
        int i = 0;
        for(; i < n; i ++)
        {
            if(nums[i]& lsb)
                type1 ^= nums[i];
            else
                type2 ^= nums[i];

            if(i & lsb)
                type1 ^= i;
            else
                type2^=i;
        }
        for(;i < n + 3; i++)
        {
            if(i & lsb)
                type1 ^= i;
            else
                type2^=i;
        }
        return{type1, type2};
    }
};