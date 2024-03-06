# set

## 原理
set原理是红黑树

## 降序
```c++
#include <iostream>
#include <set>

bool myCompare(int a, int b) {
    return a > b; // 自定义比较函数，按降序排列
}

int main() {
    std::set<int, decltype(&myCompare)> mySet(&myCompare);

    mySet.insert(3);
    mySet.insert(1);
    mySet.insert(4);
    mySet.insert(1); // 重复元素将被忽略

    for (auto it = mySet.begin(); it != mySet.end(); it++) {
        std::cout << *it << " ";
    }
    // 输出结果为：4 3 1
    return 0;
}
```

```c++
class Solution {
public:
    bool myCompare(pair<int,int> a, pair<int,int> b) {
        return a.first == b.first? a.second > b.second : a.first > b.first;
    }
    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = arr.size();
        set<pair<int,int>, bool (Solution::*)(std::pair<int, int> a, std::pair<int, int> b)> numId(myCompare);
        numId.emplace(arr[n - 1], n - 1);
        for(int i = n - 2; i >= 0; i--){
            if(arr[i] > numId.begin()->first){
                
            }
        }
        return arr;
    }
};

/////////////////////////////////////////////
bool myCompare(pair<int,int> a, pair<int,int> b) {
    return a.first == b.first? a.second > b.second : a.first > b.first;
}

class Solution {
public:

    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = arr.size();
        set<pair<int,int>, bool (std::pair<int, int> a, std::pair<int, int> b)> numId(myCompare);
        numId.emplace(arr[n - 1], n - 1);
        for(int i = n - 2; i >= 0; i--){
            if(arr[i] > numId.begin()->first){
                
            }
        }
        return arr;
    }
};
```

## 迭代器取前一个值
* 迭代器可以`int id = prev(numId.lower_bound({arr[i], -1}))->second;`
* 也可以`auto it = mySet.lower_bound(3); it--;`
* 但不能直接`mySet.lower_bound(3)--`

## 遍历
```c++
std::set<int> mySet {1, 2, 3, 4, 5};
for (std::set<int>::const_iterator it = mySet.begin(); it != mySet.end(); ++it) {
    std::cout << *it << " ";
}
// 输出：1 2 3 4 5
```
```c++
std::set<int> mySet {1, 2, 3, 4, 5};
for (auto element : mySet) {
    std::cout << element << " ";
}
// 输出：1 2 3 4 5

```

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