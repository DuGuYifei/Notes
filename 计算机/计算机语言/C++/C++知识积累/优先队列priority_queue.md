# 优先队列priority_queue

1. [基本语法，默认，less，greater](#基本语法默认lessgreater)
2. [自写cmp或重载 \> \<](#自写cmp或重载--)
3. [pair比较](#pair比较)
4. [修改值](#修改值)


## 基本语法，默认，less，greater
[priority_queue](优先队列greater和less.md)

`priority_queue<Type, Container, Functional>`\
默认大根堆，即`Functional`是`less`

```cpp
#include <queue>
//对于基础类型 默认是大顶堆
priority_queue<int> a; 
//等同于 priority_queue<int, vector<int>, less<int> > a;

priority_queue<int, vector<int>, greater<int>> c;  //这样就是小顶堆
priority_queue<string> b;
```

## 自写cmp或重载 > <

**！！！注意：return left < right 是大根堆**

1. 可以自己写一个cmp
```cpp
struct Node {
    　　int i,j;
} node[200];

struct cmp {
    bool operator() (Node a,Node b) {
        if(a.i==b.i)
            return a.j<b.j;   //j的降序
        return a.i<b.i;　　　　//i的降序
        }
};

priority_queue<Node,vector<Node>,cmp> re;
```
```cpp
auto cmp = [&](const int &a, const int &b) { return freq[a] > freq[b]; };
priority_queue<int, vector<int>, decltype(cmp)> qu;

function<bool(const pair<int, int>, const pair<int, int>)> cmp = [&](const pair<int, int>& a,const pair<int, int>& b){
        return min(a.first, a.second) > min(b.first, b.second);
    };
    priority_queue<pair<int, int>, vector<pair<int,int>>, decltype(cmp)>qu;
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

## pair比较
`priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> minVal;`\
pair的比较规则：先比较第一个元素，第一个相等比较第二个。

## 修改值
只能修改顶值，需要pop->modify->push