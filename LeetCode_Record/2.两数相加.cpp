/*
 * @lc app=leetcode.cn id=2 lang=cpp
 *
 * [2] 两数相加
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
public:rs(ListNode *l1, ListNode *l2)
    {
    ListNode *addTwoNumbe
        ListNode *list = new ListNode(0);
        ListNode *current = list;
        ListNode *before = nullptr;
        // ListNode *l1 = l1;
        // ListNode *l2 = l2;
        while (true)
        {
            //bool flag1 = (l1!=nullptr);
            //bool flag2 = (l2!=nullptr);

            if (l1 && l2)
            {
                current->val += l1->val + l2->val;
                l1 = l1->next;
                l2 = l2->next;
            }
            else if (l1)
            {
                current->val += l1->val;
                l1 = l1->next;
            }
            else if (l2)
            {
                current->val += l2->val;
                l2 = l2->next;
            }
            else
            {
                if (current->val == 0)
                {
                    before->next = nullptr;
                    delete (current);
                }
                break;
            }

            if (current->val >= 10)
            {
                current->val -= 10;
                current->next = new ListNode(1);
            }
            else
                current->next = new ListNode(0);

            before = current;
            current = current->next;
        }
        return list;
    }
};
// @lc code=end
