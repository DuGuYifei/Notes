/*
 * @lc app=leetcode.cn id=707 lang=cpp
 *
 * [707] 设计链表
 */

// @lc code=start
struct Node
{
    int val;
    Node* next;
    Node(int v):val(v){
        next = nullptr;
    }
    Node(int v, Node* n):val(v), next(n){};
};
class MyLinkedList {
private:
    int n = 0;
    Node* head = nullptr;
    Node* end = nullptr;
public:
    MyLinkedList() {
    }
    
    int get(int index) {
        if(index >= n)
            return -1;
        Node* cur = head;
        while(index > 0)
        {
            cur = cur->next;
            index--;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        Node* nn = new Node(val, head);
        head = nn;
        if(!n)
        {
            end = head;
        }
        n++;
    }
    
    void addAtTail(int val) {
        Node* e = new Node(val);
        if(!n)
        {
            head = e;
            end = e;
        }
        else{
            end -> next = e;
            end = e;
        }
        n++;
    }
    
    void addAtIndex(int index, int val) {
        if(index <= 0)
        {
            addAtHead(val);
            return;
        }
        else if(index > n)
            return;
        else if(index == n)
        {
            addAtTail(val);
            return;
        }
        else
        {
            Node* cur = head;
            index--;
            while(index > 0)
            {
                cur = cur->next;
                index--;
            }
            Node* temp = cur->next;
            cur->next = new Node(val, temp);
        }
        n++;
    }
    
    void deleteAtIndex(int index) {
        if(index >= n)
            return;
        n--;
        if(!n)
        {
            delete(head);
            head = nullptr;
            end = nullptr;
            return;
        }
        Node* cur = head;
        index--;
        if(!(~index))
        {
            head = head->next;
            delete (cur);
            return;
        }
        while(index > 0)
        {
            cur = cur->next;
            index--;
        }
        Node* temp = cur->next;
        cur->next = temp->next;
        if(!cur->next)
            end = cur;
        delete (temp);
    }
};
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
// @lc code=end
