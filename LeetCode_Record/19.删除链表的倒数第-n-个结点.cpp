/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *temp = head;
        int length = 0;
        while (temp != nullptr)
        {
            length++;
            temp = temp->next;
        }
        length = length - n;
        if(length == 0)
        {
            return head -> next;
        }
        ListNode *prev = head;
        temp = head;
        while (length != 0)
        {
            length--;
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        return head;
    }
};
// @lc code=end
