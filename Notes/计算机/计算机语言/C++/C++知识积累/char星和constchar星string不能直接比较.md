# char星和constchar星string不能直接比较

char*是个很麻烦的事务不能直接与后两者比较

也不能用
char* a = "asdhf" 来赋值。

[C++ const char*和char* 比较 与 二维字符数组 const char* const* 与 char* strModel1[] - 赠君破阵歌 - 博客园](https://www.cnblogs.com/dengyuting666/p/9729458.html)

[c++中string、const char*和char*之间的相互转换_zhaofrjx的专栏-CSDN博客](https://blog.csdn.net/zhaofrjx/article/details/51056799)

[string转为constchar星指针c_str()](string转为constchar星指针c_str().md)

## char* 和 string
`string s(char*)` 就行, 但是要注意，如果

```cpp
char* ans = (char*)malloc(n + 2);
```
一定要在结束的位置加上`\0`，不然输出会有问题，string不知道到哪里结束，有的编译器会超出范围输出，有的直接报错