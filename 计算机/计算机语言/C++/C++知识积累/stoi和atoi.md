# stoi和atoi


## 区别

1. `stoi(str)` 是可以把字符串转换为整数的函数，`atoi(s.c_str())` 也是可以把字符串转换为整数的函数，`stoi` 是 C++11 标准引入的，而 `atoi` 是 C 语言中的函数。两者的区别在于：

2. `stoi` 是 C++ 的函数，接受一个 `std::string` 类型的参数，而 `atoi` 是 C 的函数，接受一个 C 风格字符串（即 `const char*`）作为参数。


## stoi

`stoi(str, pos, base)`， 比如 `stoi("101", nullptr, 2)`，会把字符串 "101" 解析为二进制数。

```cpp
size_t pos; // 解析结束的位置
int num = stoi("123abc", &pos); // num = 123, pos = 3，因为解析到 'a' 时停止了，把终止位置存储在 pos 中
```