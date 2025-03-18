#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=307 lang=cpp
 *
 * [307] 区域和检索 - 数组可修改
 */

// @lc code=start
// class NumArray {
//     vector<int> nums;
// public:
//     NumArray(vector<int>& nums) {
//         this->nums = nums;
//     }

//     void update(int index, int val) {
//         nums[index] = val;
//     }

//     int sumRange(int left, int right) {
//         int sum = 0;
//         for(int i = left; i<=right;i++)
//             sum+=nums[i];
//         return sum;
//     }
// };

// 线段树
// class NumArray
// {
//     // 线段树
//     vector<int> segmentTree;
//     int n;
//     // l(left)和r(right)是nums的index, 同时是node所涵盖的范围
//     void build(int node, int l, int r, vector<int> &nums)
//     {
//         if (l == r)
//         {
//             segmentTree[node] = nums[l];
//             return;
//         }
//         build(node * 2 + 1, l, (l + r) / 2, nums);
//         build(node * 2 + 2, (l + r) / 2 + 1, r, nums);
//         segmentTree[node] = segmentTree[node * 2 + 1] + segmentTree[node * 2 + 2];
//     }

//     // 直接对相关节点重新建立即可，没必要计算差值再算，否则会多个返回值
//     void change(int index, int val, int node, int l, int r)
//     {
//         if (l == r)
//         {
//             segmentTree[node] = val;
//             return;
//         }
//         // 判断要改的值在该sum节点的左分支还是右分支
//         if (index <= (l + r) / 2)
//             change(index, val, node * 2 + 1, l, (l + r) / 2);
//         else
//             change(index, val, node * 2 + 2, (l + r) / 2 + 1, r);

//         segmentTree[node] = segmentTree[node * 2 + 1] + segmentTree[node * 2 + 2];
//     }

//     int sum(int rangeL, int rangeR, int node, int l, int r)
//     {
//         if (rangeL == l && rangeR == r)
//         {
//             return segmentTree[node];
//         }

//         // 在左分支
//         if (rangeR <= (l + r) / 2)
//         {
//             return sum(rangeL, rangeR, node * 2 + 1, l, (l + r) / 2);
//         }
//         // 在右分支
//         else if (rangeL > (l + r) / 2)
//         {
//             return sum(rangeL, rangeR, node * 2 + 2, (l + r) / 2 + 1, r);
//         }
//         // 跨左右分支，还得拆
//         else
//         {
//             return sum(rangeL, (l + r) / 2, node * 2 + 1, l, (l + r) / 2) +
//                    sum((l + r) / 2 + 1, rangeR, node * 2 + 2, (l + r) / 2 + 1, r);
//         }
//     }

// public:
//     NumArray(vector<int> &nums) : n(nums.size()), segmentTree(nums.size() * 4) // 1 + 2 + 4 + 8 + ... + n(即2^(index-1) = n) = 1 * (1-2n)/(1-2) = 2n - 1
//     {
//         build(0, 0, n - 1, nums);
//     }

//     void update(int index, int val)
//     {
//         change(index, val, 0, 0, n - 1);
//     }

//     int sumRange(int left, int right)
//     {
//         return sum(left, right, 0, 0, n - 1);
//     }
// };

// 树状数组
class NumArray
{
private:
    vector<int> &nums; // 原数组
    vector<int> tree;  // 树状数组
public:
    int lowBit(int x)
    {
        return x & (-x);
    }

    NumArray(vector<int> &nums) : nums(nums)
    {
        int n = nums.size();
        tree = vector<int>(n + 1, 0);
        // 构造树状数组
        for (int i = 1; i <= n; i++)
        {
            tree[i] += nums[i - 1];
            // 同时加到父节点里
            // i + lowBit(i) : 6 (110) + 2 (10) = 8 (1000)
            if (i + lowBit(i) <= n)
                tree[i + lowBit(i)] += tree[i];
        }
    }

    void update(int index, int val)
    {
        int d = val - nums[index];
        // 修改每一个影响到的节点
        for (int i = index + 1; i <= tree.size() - 1; i += lowBit(i))
            tree[i] += d;
        // 修改原数组
        nums[index] = val;
    }

    int sumRange(int left, int right)
    {
        int r = 0, l = 0;
        // 前left和
        for (int i = right + 1; i >= 1; i -= lowBit(i))
            r += tree[i];
        // 前right和
        for (int i = left; i >= 1; i -= lowBit(i))
            l += tree[i];
        return r - l;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
// @lc code=end
