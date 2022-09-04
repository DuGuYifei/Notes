# 类里auto直接获得函数类型

这里auto 是可以的
```cpp
    static constexpr auto hash_t = [fn = hash<int>()](const tuple<int,int,int>& t)->size_t{
        auto &[x,y,z] = t;
        return fn(x)<< 16 ^ fn(y) << 8 ^ fn(z);
    };
```
constexpr auto 是不行的
static auto 也不行
