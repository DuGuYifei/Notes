/*
 * @lc app=leetcode.cn id=622 lang=cpp
 *
 * [622] 设计循环队列
 */

// @lc code=start
class MyCircularQueue
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x) { next = nullptr; }
    };

private:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    int capacity = -1;
    int size = 0;

public:
    MyCircularQueue(int k) : capacity(k){};

    bool enQueue(int value)
    {

        if (size < capacity)
        {
            if (size == 0)
            {
                head = new ListNode(value);
                tail = head;
                size++;
                return true;
            }
            tail->next = new ListNode(value);
            tail = tail->next;
            size++;
            return true;
        }
        return false;
    }

    bool deQueue()
    {
        if (size == 0)
            return false;
        size--;
        ListNode *node = head;
        head = head->next;
        delete node;
        return true;
    }

    int Front()
    {
        if (size == 0)
            return -1;
        return head->val;
    }

    int Rear()
    {
        if (size == 0)
            return -1;
        return tail->val;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    bool isFull()
    {
        return size == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
// @lc code=end
