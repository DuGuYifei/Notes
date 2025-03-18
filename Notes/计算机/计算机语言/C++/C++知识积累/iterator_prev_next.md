# iterator_prev_next

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