## 优先队列greater<>和less<>
[priority_queue](优先队列priority_queue.md)

源码中：
* greater 是 大于号
* less 是小于号

原理：红黑树

[c++优先队列 less和greater - 元禛慎独的个人空间 - OSCHINA - 中文开源技术交流社区](https://my.oschina.net/lCQ3FC3/blog/828571)

# 例1
```cpp
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
 
template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}
 
int main() {
  std::priority_queue<int> q;
 
  for(int n : {1,8,5,6,3,4,0,9,7,2})
      q.push(n);
 
  print_queue(q);
 
  std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
 
  for(int n : {1,8,5,6,3,4,0,9,7,2})
      q2.push(n);
 
  print_queue(q2);
}

//输出：
//9 8 7 6 5 4 3 2 1 0  // less
//0 1 2 3 4 5 6 7 8 9   //greater
```

## 例2
注意：这里将`<`写成了`>`号的功能，这样就将less大根堆变成了小根堆，因为`less`用的`小于号`，`greater`用的`大于号`
```cpp
class Solution {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue <Status> q;

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top(); q.pop();
            tail->next = f.ptr; 
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/he-bing-kge-pai-xu-lian-biao-by-leetcode-solutio-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```