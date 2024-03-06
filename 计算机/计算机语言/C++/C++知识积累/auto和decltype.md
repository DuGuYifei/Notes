# auto 和 decltype
1. [auto](#auto)
2. [decltype](#decltype)
3. [auto[a,b]的类型](#autoab的类型)

## auto
`auto`相当于`c#`里的`var`

## decltype
`decltype`类型说明符，可以选择并返回操作数的数据类型

[【C++深陷】之“decltype”\_不能自拔-CSDN博客\_decltype](https://blog.csdn.net/u014609638/article/details/106987131/)

```cpp
// sum的类型就是函数f返回的类型
decltype(f()) sum = x;

const int ci = 0, &cj = ci;

// x的类型是const int
decltype(ci) x = 0;

// y的类型是const int &
decltype(cj) y = x;
```

例：用decltype获得一个函数的类型，不用写function类型省事
```cpp
auto hash_p = [](const pair<int, int> &p) -> size_t {
    static hash<long long> hash_ll;
    return hash_ll(p.first + (static_cast<long long>(p.second) << 32));
};
unordered_set<pair<int, int>, decltype(hash_p)> points(0, hash_p);
```


## auto[a,b]的类型

Structured binding declaration (since C++17)
所以vs studio里面要在工程文件右键属性，c/c++里修改版本

```c++
auto [left1, right1] = TwoSides(s, i, i);
auto [left2, right2] = TwoSides(s, i, i + 1);

pair<int, int> TwoSides(string s, int left, int right){};
```

如上例，left1,right1 经VS Studio监视变量，类型是`int&&`。