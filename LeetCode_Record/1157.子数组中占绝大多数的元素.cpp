#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
using namespace std;
/*
 * @lc app=leetcode.cn id=1157 lang=cpp
 *
 * [1157] 子数组中占绝大多数的元素
 *
 * https://leetcode.cn/problems/online-majority-element-in-subarray/description/
 *
 * algorithms
 * Hard (35.57%)
 * Likes:    96
 * Dislikes: 0
 * Total Accepted:    6.3K
 * Total Submissions: 15.9K
 * Testcase Example:  '["MajorityChecker","query","query","query"]\n' +
  '[[[1,1,2,2,1,1]],[0,5,4],[0,3,3],[2,3,2]]'
 *
 * 设计一个数据结构，有效地找到给定子数组的 多数元素 。
 * 
 * 子数组的 多数元素 是在子数组中出现 threshold 次数或次数以上的元素。
 * 
 * 实现 MajorityChecker 类:
 * 
 * 
 * MajorityChecker(int[] arr) 会用给定的数组 arr 对 MajorityChecker 初始化。
 * int query(int left, int right, int threshold) 返回子数组中的元素  arr[left...right]
 * 至少出现 threshold 次数，如果不存在这样的元素则返回 -1。
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入:
 * ["MajorityChecker", "query", "query", "query"]
 * [[[1, 1, 2, 2, 1, 1]], [0, 5, 4], [0, 3, 3], [2, 3, 2]]
 * 输出：
 * [null, 1, -1, 2]
 * 
 * 解释：
 * MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
 * majorityChecker.query(0,5,4); // 返回 1
 * majorityChecker.query(0,3,3); // 返回 -1
 * majorityChecker.query(2,3,2); // 返回 2
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= arr.length <= 2 * 10^4
 * 1 <= arr[i] <= 2 * 10^4
 * 0 <= left <= right < arr.length
 * threshold <= right - left + 1
 * 2 * threshold > right - left + 1
 * 调用 query 的次数最多为 10^4 
 * 
 * 
 */

// @lc code=start

struct Node
{
    int x, cnt;
    Node(int x = 0, int cnt = 0) :x(x), cnt(cnt) {}
    Node& operator +=(const Node& that){
        if(this->x == that.x){
            this->cnt += that.cnt;
        }else if(this->cnt < that.cnt){
            this->x = that.x;
            this->cnt = that.cnt - this->cnt;
        }else{
            this->cnt -= that.cnt;
        }
        return *this;
    }
};


class MajorityChecker {
private:
    vector<int>& arr;
    vector<Node> tree;
    unordered_map<int, vector<int>> pos;
public:
    MajorityChecker(vector<int>& arr) : arr(arr) {
        int n = arr.size();
        tree.resize(n << 2);
        seg_build(0, n - 1, 0);
        for(int i = 0; i < n; i++){
            pos[arr[i]].emplace_back(i);
        }
    }

    void seg_build(int l, int r, int p){
        if(l == r){
            tree[p] = Node(arr[l], 1);
            return;
        }
        int mid = (l + r) >> 1;
        seg_build(l, mid, (p << 1) + 1);
        seg_build(mid + 1, r, (p << 1) + 2);
        tree[p] += tree[(p << 1) + 1];
        tree[p] += tree[(p << 1) + 2];
    }

    Node seg_query(int l, int r, int s, int t, int p){
        if(l <= s && r >= t){
            return tree[p];
        }
        int mid = s + ((t - s) >> 1);
        Node res = Node();
        if(l <= mid)
            res += seg_query(l, r, s, mid, (p << 1) + 1);
        if(r > mid)
            res += seg_query(l, r, mid + 1, t, (p << 1) + 2);
        return res;
    }

    int query(int left, int right, int threshold) {
        Node res = seg_query(left, right, 0, arr.size() - 1, 0);
        int cnt = upper_bound(pos[res.x].begin(), pos[res.x].end(), right) - lower_bound(pos[res.x].begin(), pos[res.x].end(), left);
        if(cnt < threshold)
            return -1;
        return res.x;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
// @lc code=end

