#include <unordered_set>
#include <vector>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*
 * @lc app=leetcode.cn id=817 lang=cpp
 *
 * [817] 链表组件
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
    int numComponents(ListNode* head, vector<int>& nums) {
        // unordered_map<int, char> list;
        // ListNode* temp= head;
        // while(temp)
        // {
        //     list[temp->val] = 'a';
        //     temp = temp->next;
        // }
        // for(auto& i : nums)
        // {
        //     if(list[i] == 'a')
        //         list[i] = 'b';
        // }
        // int ans = 0;
        // char prev = 'a';
        // while(head)
        // {
        //     if(list[head->val] == 'b')
        //     {
        //         if(prev == 'a')
        //         {
        //             ans++;
        //             prev = 'b';
        //         }
        //     }
        //     else if(prev == 'b')
        //     {
        //         prev = 'a';
        //     }

        //     head = head->next;
        // }
        // return ans;

        unordered_set<int> st;
        for(int& i: nums)
            st.insert(i);
        int ans = 0;
        bool prev = false;
        while(head)
        {
            if(st.count(head->val))
            {
                if(!prev)
                {
                    ans++;
                    prev = true;
                }
            }
            else
                prev = false;
            head = head->next;
        }
        return ans;
    }
};
// @lc code=end

