# 优先队列priority_queue
`priority_queue<Type, Container, Functional>`\
默认大根堆，即`Functional`是`less`
1. 可以自己写一个cmp
```cpp
struct Node {
    　　int i,j;
} node[200];

struct cmp {
    bool operator() (Node a,Node b) {
        if(a.i==b.i)
            return a.j<b.j;///j的升序
        return a.i<b.i;　　　　///i的升序
        }
};

priority_queue<Node,vector<Node>,cmp> re;
```
2. 也可以直接重载原类型的 `>`和`<`
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

```cpp
#include <queue>
//对于基础类型 默认是大顶堆
priority_queue<int> a; 
//等同于 priority_queue<int, vector<int>, less<int> > a;

//          这里一定要有空格，不然成了右移运算符↓(不需要)
priority_queue<int, vector<int>, greater<int> > c;  //这样就是小顶堆
priority_queue<string> b;
```

`priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> minVal;`\
pair的比较规则：先比较第一个元素，第一个相等比较第二个。