# struct作为模板T声明变量
```cpp
    struct Status{
        int val;
        ListNode* ptr;
        // 因为这个重载不能写入原本的struct，所以新建一个struct也行
        bool operator < (const Status &s) const{
            return val > s.val;
        }
    };

    priority_queue<Status> q;
    for(auto i:lists)
    {
        if(i)
            q.push({i->val, i});
    }
```