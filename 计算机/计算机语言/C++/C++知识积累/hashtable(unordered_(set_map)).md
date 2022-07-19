# hashtable `(`unordered_set/map)

#### `map` 和 `unordered map`区别：

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

#### 自己写hash给特殊的unordered_set
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

#### count()
unordered_set.count()

#### insert() 和 erase()
unordered_set.insert()\
unordered_set.erase()\
unordered_set.find()\
这三个函数平均复杂度是O(1)因为这个是哈希表不是数组要一个一个查
