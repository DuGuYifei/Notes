/*
 * @lc app=leetcode.cn id=641 lang=cpp
 *
 * [641] 设计循环双端队列
 */

// @lc code=start
struct Node{
    int val;
    Node *prev, *next;
    Node(int v, Node* p, Node* n):val(v), prev(p), next(n){};
};

class MyCircularDeque {
private:
    int size = 0;
    int capacity;
    Node*head, * tail;
public:
    MyCircularDeque(int k):capacity(k){
    }
    
    bool insertFront(int value) {
        if(size >= capacity)
            return false;
        size++;
        if(size == 1)
        {
            head = new Node (value, nullptr, nullptr);
            tail = head;
        }
        else
        {
            Node* temp = new Node(value, nullptr, head);
            head->prev = temp;
            head = temp;
        }
        return true;
    }
    
    bool insertLast(int value) {
        if(size >= capacity)
            return false;
        size++;
        if(size == 1)
        {
            head = new Node (value, nullptr, nullptr);
            tail = head;
        }
        else
        {
            Node* temp = new Node(value, tail, nullptr);
            tail->next = temp;
            tail = temp;
        }
        return true;
    }
    
    bool deleteFront() {
        if(size == 0)
            return false;
        Node* temp = head;
        if(size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }
        size--;
        delete temp;
        return true;
    }
    
    bool deleteLast() {
        if(size == 0)
            return false;
        Node* temp = tail;
        if(size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        size--;
        delete temp;
        return true;
    }
    
    int getFront() {
        if(size)
            return head->val;
        return -1;
    }
    
    int getRear() {
        if(size)
            return tail->val;
        return -1;
    }
    
    bool isEmpty() {
        return !size;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
// @lc code=end

