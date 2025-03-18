/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        // if (list1 == nullptr) return list2;
        // else if (list2 == nullptr) return list1;

        // ListNode* current = list1;
        // ListNode* prev = nullptr;
        // ListNode* med = nullptr;
        // while (true)
        // {
        //     if (list2 == nullptr)
        //         break;

        //     if (current->val >= list2->val)
        //     {
        //         med = list2;
        //         list2 = list2->next;
        //         med->next = current;
        //         if (prev != nullptr)prev->next = med;
        //         else list1 = med;
        //         prev = med;
        //     }
        //     else
        //     {
        //         prev = current;
        //         current = current->next;
        //         if (current == nullptr)
        //         {
        //             prev->next = list2;
        //             break;
        //         }
        //     }
        // }
        // return list1;
        ListNode* preHead = new ListNode(-1);

        ListNode* prev = preHead;
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }

        // 合并后 list1 和 list2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = list1 == nullptr ? list2 : list1;

        return preHead->next;
    }
};
// @lc code=end
