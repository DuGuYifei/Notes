# hashtable (unordered_set/map)

1. [`map` 和 `unordered map`区别：](#map-和-unordered-map区别)
2. [自己写hash给特殊的unordered\_set](#自己写hash给特殊的unordered_set)
3. [自定义hash](#自定义hash)
4. [遍历unordered\_map](#遍历unordered_map)
5. [遍历unoreder\_set](#遍历unoreder_set)
6. [声明](#声明)
   1. [string/vector/其他container](#stringvector其他container)
7. [函数](#函数)
   1. [count()](#count)
   2. [insert() 和 erase()](#insert-和-erase)
   3. [find](#find)


## `map` 和 `unordered map`区别：

```c++
//前者是红黑树，有序的，后者是无序的哈希表
map.find() //返回查找的iteration, iteration里有key+value见下一条,找不到返回`map.end()`
map.end()  //返回最后元素的旁边
```

`map->first/second` 就是键/值

`unordered_set` and `unordered_map` 都是哈希表

`set` and `map` 都是红黑树

set是只有值（其实有键，但是用不着），map是键值对

向unordered_map中插入键值对，\
key不同value相同可以，\
key相同后一个插入失败，（`insert` or `emplace`）\
但是用**下标**插入key相同会被覆盖（`a[key]=`）\
同理没有这个key，**下标**插入会自动创建，默认是0
```cpp
    unordered_map<int, char>a;
    a[0]+=98;
    cout << a[0];
    return 0;
    //输出 b
```

## 自己写hash给特殊的unordered_set
[hash](hash和自构建hash函数给hashset.md)

有时候，unordered_set 不会处理一些类型，需要自己写hash
- 例1：
  ```cpp
  auto hash_p = [](const pair<int, int> &p) -> size_t {
    static hash<long long> hasSh_ll;
    return hash_ll(p.first + (static_cast<long long>(p.second) << 32));
  };
  unordered_set<pair<int, int>, decltype(hash_p)> points(0, hash_p);
  ```
- 例2：
  ```cpp
  struct pair_hash
  {
      template <class T1, class T2>
      size_t operator () (pair<T1, T2> const &pair) const
      {
          size_t h1 = hash<T1>()(pair.first); //用默认的 hash 处理 pair 中的第一个数据 X1
          size_t h2 = hash<T2>()(pair.second);//用默认的 hash 处理 pair 中的第二个数据 X2
          return h1 ^ h2;
      }
  };
  ```
- 例3
  ```cpp
  auto hash_p = [](const pair<int, int> &p)
  {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
  };
  unordered_set<pair<int, int>, decltype(hash_p)> lamp(0, hash_p);
  ```

## 自定义hash
[自定义](hash和自构建hash函数给hashset.md)
```cpp
    static constexpr auto hash_t = [fn = hash<int>()](const tuple<int,int,int>& t)->size_t{
        auto &[x,y,z] = t;
        return fn(x)<< 16 ^ fn(y) << 8 ^ fn(z);
    };
    unordered_map<tuple<int,int,int>, pair<TreeNode*, int>, decltype(hash_t)> t_map{0, hash_t};
```
注意声明时那个0，是size_type


## 遍历unordered_map
输出顺序是 **是乱序的**，因为会根据hash值放入不同的bucket里。

```cpp
for(pair<int,int> kv:map){
  cout<<kv.first<<kv.second<<endl;
}

for(auto kv:map){
  cout<<kv.first<<kv.second<<endl;
}
for(auto&& [_,v]:map){
  cout<<v<<endl;
}
///////////////////////////////////////////////

for(unordered_map<int,int>::iterator it=map.begin();it!=map.end();it++){
  cout<<it->first<<it->second<<endl;
}

for(auto it=map.begin();it!=map.end();it++){
  cout<<it->first<<it->second<<endl;
}
```

## 遍历unoreder_set
```c++
    unordered_set<int> a;
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(5);
    a.insert(4);
    for (auto& i : a)
        cout << i;

    cout << endl;

    unordered_set <int> b = { 1,2,3,5,4 };
    for (auto& i : b)
        cout << i;
    cout << endl;

    for (unordered_set<int>::iterator it = b.begin(); it != b.end(); it++)
        cout << *it << " ";
-----------------------------
输出：
12354
12354
1 2 3 5 4
```

## 声明
### string/vector/其他container
```cpp
class Solution {
public:
    string greatestLetter(string s) {
        unordered_set<char> ht(s.begin(), s.end());
        for (int i = 25; i >= 0; i--) {
            if (ht.count('a' + i) > 0 && ht.count('A' + i) > 0) {
                return string(1, 'A' + i);
            }
        }
        return "";
    }
};
```

## 函数
### count()
unordered_set.count()

### insert() 和 erase()
unordered_set.insert()\
unordered_set.erase()\
unordered_set.find()\
这三个函数平均复杂度是O(1)因为这个是哈希表不是数组要一个一个查

### find
1. **注意用的是end，不是back**
2. **因为找完，如果遍历输出会发现，find的key第一个出现了，即最后插入了它**
```cpp
t_map.find(key) != t_map.end()
```