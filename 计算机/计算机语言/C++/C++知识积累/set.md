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

