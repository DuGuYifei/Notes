#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=870 lang=cpp
 *
 * [870] 优势洗牌
 */

// @lc code=start
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> id1(n), id2(n);
        iota(id1.begin(), id1.end(), 0);
        iota(id2.begin(), id2.end(), 0);
        sort(id1.begin(), id1.end(), [r = nums1.data()](const int& a,const int& b){
            return r[a] < r[b];
        });
        sort(id2.begin(), id2.end(), [r = nums2.data()](const int& a,const int& b){
            return r[a] < r[b];
        });
        int j = 0, id2Back = n - 1;;
        vector<int> ans(n);
        for(auto& i : id1)
        {
            if(nums1[i] <= nums2[id2[j]])
                ans[id2[id2Back--]] = nums1[i];
            else
                ans[id2[j++]] = nums1[i];
        }
        return ans;
    }
};
// @lc code=end

