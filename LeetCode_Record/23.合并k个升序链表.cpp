#include <vector>
#include <queue>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*
 * @lc app=leetcode.cn id=23 lang=cpp
 *
 * [23] 合并K个升序链表
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
    struct Status{
        int val;
        ListNode* ptr;
        // 因为这个重载不能写入原本的struct，所以新建一个struct也行
        bool operator < (const Status &s) const{
            return val > s.val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<Status> q;
        for(auto i:lists)
        {
            if(i)
                q.push({i->val, i});
        }
        if(q.empty())
           return 0; 
        ListNode* merge = q.top().ptr;
        q.pop(); 
        if(merge->next)
            q.push({merge->next->val, merge->next});
        ListNode* head = merge;
        while(!q.empty())
        {
            head->next = q.top().ptr;
            head = head->next;
            q.pop();
            if(head->next)
                q.push({head->next->val,head->next});
        }
        return merge;
    }
};
// @lc code=end

