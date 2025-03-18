/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
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
    ListNode* swapPairs(ListNode* head) {
        // ListNode* first = head;
        // if(!head)
        //     return 0;
        // if(!head->next)
        //     return head;
        
        // ListNode* second = head->next;
        // ListNode* ans = second;
        // ListNode* prev = new ListNode(0, head);
        // while(second != nullptr && first != nullptr)
        // {
        //     ListNode* temp = second->next;
        //     second->next=first;
        //     first->next = temp;
        //     prev->next = second;

        //     prev = first;
        //     first = first->next;
        //     if(first)
        //         second = first->next;
        // }
        // return ans;
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;
        return newHead;
    }
};
// @lc code=end

