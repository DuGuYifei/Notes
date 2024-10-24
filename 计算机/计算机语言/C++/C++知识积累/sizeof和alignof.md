# sizeof和alignof

## 简介

* sizeof 是用于获取类型或对象的大小，以字节为单位。
* alignof 是用于获取类型或对象的对齐要求，即对象应该对齐到的内存边界。

对于一个结构体或者类，sizeof 返回的是该结构体或类的实例所占用的内存大小，而 alignof 返回的是该结构体或类的实例应该对齐到的内存边界，往往

1. alignof是该结构体或类中成员变量中对齐要求最大的那个。
2. sizeof是alignof的倍数。因为每个都会对齐到alignof的倍数。

## 示例

```cpp
#include <iostream>

struct Example {
    char c;
    int i;
};

int main() {
    std::cout << "Size of Example: " << sizeof(Example) << " bytes" << std::endl;
    std::cout << "Alignment of Example: " << alignof(Example) << " bytes" << std::endl;
    return 0;
}
/*
Size of Example: 8 bytes
Alignment of Example: 4 bytes
*/
```