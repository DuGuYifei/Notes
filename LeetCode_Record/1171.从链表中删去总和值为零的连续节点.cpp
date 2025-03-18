#include <vector>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*
 * @lc app=leetcode.cn id=1171 lang=cpp
 *
 * [1171] 从链表中删去总和值为零的连续节点
 *
 * https://leetcode.cn/problems/remove-zero-sum-consecutive-nodes-from-linked-list/description/
 *
 * algorithms
 * Medium (48.32%)
 * Likes:    204
 * Dislikes: 0
 * Total Accepted:    21.7K
 * Total Submissions: 44.3K
 * Testcase Example:  '[1,2,-3,3,1]'
 *
 * 给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。
 * 
 * 删除完毕后，请你返回最终结果链表的头节点。
 * 
 * 
 * 
 * 你可以返回任何满足题目要求的答案。
 * 
 * （注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）
 * 
 * 示例 1：
 * 
 * 输入：head = [1,2,-3,3,1]
 * 输出：[3,1]
 * 提示：答案 [1,2,1] 也是正确的。
 * 
 * 
 * 示例 2：
 * 
 * 输入：head = [1,2,3,-3,4]
 * 输出：[1,2,4]
 * 
 * 
 * 示例 3：
 * 
 * 输入：head = [1,2,3,-3,-2]
 * 输出：[1]
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 给你的链表中可能有 1 到 1000 个节点。
 * 对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.
 * 
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        unordered_map<int, ListNode*> map;
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* cur = dummy;
        int sum = 0;
        while (cur) {
            sum += cur->val;
            map[sum] = cur;
            cur = cur->next;
        }
        cur = dummy;
        sum = 0;
        while (cur) {
            sum += cur->val;
            cur->next = map[sum]->next;
            cur = cur->next;
        }
        return dummy->next;
    }
};
// @lc code=end

