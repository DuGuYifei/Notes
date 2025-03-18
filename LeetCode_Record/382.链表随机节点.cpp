#include <vector>
using namespace std;
/*
 * @lc app=leetcode.cn id=382 lang=cpp
 *
 * [382] 链表随机节点
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
    //vector<int> value;
    ListNode* header;

public:
    Solution(ListNode *head)
    {
        // ListNode *a  =  head;
        // while (a != 0)
        // {
        //     value.emplace_back(a->val);
        //     a = a->next;
        // }

        header=head;

    }

    int getRandom()
    {
        //return value[rand()% value.size()];

        int ans = 0;
        int i = 1;
        ListNode* node = header;
        for(; node ; node = node->next,i++)
        {
            if(rand()% i == 0)
            {
                ans = node->val;
            }
        }
        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
// @lc code=end
