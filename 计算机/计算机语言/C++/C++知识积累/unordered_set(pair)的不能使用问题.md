# unordered_set<pair<int,int>>的不能使用问题

[unordered_set](unordered_set-unordered_map.md)
[pair](pair.md)

[哈希表之unordered_set<pairi<nt,int>案例与分析](https://blog.csdn.net/weixin_44636463/article/details/114069120)
我们要给pair写自己的哈希函数：
案例1：
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
unordered_set<pair<int, int>, pair_hash> hash1;
```

案例2：
[力扣 1036 逃离大迷宫](https://leetcode-cn.com/problems/escape-a-large-maze/solution/tao-chi-da-mi-gong-by-leetcode-solution-qxhz/)
```cpp
auto hash_fn = [fn = hash<long long>()](const pair<int, int>& o) -> size_t {
    auto& [x, y] = o;
    return fn((long long)x << 20 | y);
};
unordered_set<pair<int, int>, decltype(hash_fn)> hash_blocked(0, hash_fn);
```

案例3：
```cpp
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};
std::unordered_set< std::pair<int, int>,  pair_hash> u_edge_;
```