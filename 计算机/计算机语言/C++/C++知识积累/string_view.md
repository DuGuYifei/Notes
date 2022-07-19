# string_view

string_view

```
std::string_view是C++ 17标准中新加入的类，正如其名，它提供一个字符串的视图，即可以通过这个类以各种方法“观测”字符串，但不允许修改字符串。由于它只读的特性，它并不真正持有这个字符串的拷贝，而是与相对应的字符串共享这一空间。即——构造时不发生字符串的复制。同时，你也可以自由的移动这个视图，移动视图并不会移动原定的字符串。
```

* 通过调用 string_view 构造器可将字符串转换为 string_view 对象。string 可隐式转换为 string_view。
* string_view 是只读的轻量对象，它对所指向的字符串没有所有权。
* string_view通常用于函数参数类型，可用来取代 const char\* 和 const string&。string_view 代替 const * string&，可以避免不必要的内存分配。
* string_view的成员函数即对外接口与 string 相类似，但只包含读取字符串内容的部分。
* string_view::substr()的返回值类型是string_view，不产生新的字符串，不会进行内存分配。string::substr()的返回值类型是string，产生新的字符串，会进行内存分配。
* string_view字面量的后缀是 sv。（string字面量的后缀是 s）

```cpp
        unordered_set<string_view> dict;
        for(const auto& i : dictionary)
        {
            dict.emplace(i);
        }
```
