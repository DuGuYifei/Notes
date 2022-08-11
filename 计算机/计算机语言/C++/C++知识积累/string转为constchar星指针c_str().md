# string转为char* str.c_str()
`c_str()` 以 `const char*` 形式传回 `string` 内含字符串，如果一个函数要求`const char*`参数，可以使用`c_str()`方法
```cpp
string s = "Hello World!";
printf("%s", s.c_str());    // 输出 "Hello World!"
```