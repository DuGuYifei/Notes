/*
 * @lc app=leetcode.cn id=2605 lang=cpp
 *
 * [2605] 从两个数字数组里生成最小数字
 */

// @lc code=start
class Solution {
public:
    int minNumber(vector<int>& nums1, vector<int>& nums2) {
        int dict[10] = {0};
        for (int& i : nums1){
            dict[i] = 1;
        }
        for (int& i : nums2) {
            dict[i] += 2;
        }
        int min1 = 9, min2 = 9;
        for(int i = 1; i <= 9; i++) {
            if (dict[i] == 3)
                return i;
            if (min1 == 9 && dict[i] == 1)
                min1 = i;
            if (min2 == 9 && dict[i] == 2)
                min2 = i;
        }
        return min1 < min2 ? min1 * 10 + min2 : min2 * 10 + min1;
    }
};
// @lc code=end

