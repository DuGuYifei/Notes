# set

## 原理
set原理是红黑树

## erase
set.erase(x)

## rbegin
`*set.rbegin()`

## find prev next
`*prev(it), *next(it)`

```cpp
set<int> seats;
priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;

void leave(int p) {
    if (p != *seats.begin() && p != *seats.rbegin()) {
        auto it = seats.find(p);
        pq.push({*prev(it), *next(it)});
    }
    seats.erase(p);
}
```

## lower_bound
```cpp
For a set of integer,
    set<int> st;
    st.insert(6);
    st.insert(4);
    st.insert(10);
    set content: //sorted always(ordered)
        4
        6
        10

    it=st.lower_bound(6)
    Print *it; //6
    it=st.lower_bound(8)
    Print *it; //10
```

* key1：lower_bound 没有的时候就是`end()`
* key2：迭代器可以`*it`

## merge
```c++
#include <iostream>
#include <set>

int main() {
    std::set<int> a = {1, 3, 5};
    std::set<int> b = {2, 4, 6};
    a.merge(b);

    for (int i : a) {
        std::cout << i << ' ';
    }

    return 0;
}

//输出
1 2 3 4 5 6
```