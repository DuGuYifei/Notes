# constexpr

`constexpr`表示这玩意儿在编译期就可以算出来（前提是为了算出它所依赖的东西也是在编译期可以算出来的）。

`const`只保证了运行时不直接被修改（但这个东西仍然可能是个动态变量）。

```cpp
#include <iostream>
#include <array>
using namespace std;
void dis_1(const int x){
    //错误，x是只读的变量
    array <int,x> myarr{1,2,3,4,5};
    cout << myarr[1] << endl;
}
void dis_2(){
    const int x = 5;
    array <int,x> myarr{1,2,3,4,5};
    cout << myarr[1] << endl;
}
int main()
{
   dis_1(5);
   dis_2();
}
```

可以看到，dis_1() 和 dis_2() 函数中都包含一个 const int x，但 dis_1() 函数中的 x 无法完成初始化 array 容器的任务，而 dis_2() 函数中的 x 却可以。

这是因为，dis_1() 函数中的“const int x”只是想强调 x 是一个只读的变量，其本质仍为变量，无法用来初始化 array 容器；而 dis_2() 函数中的“const int x”，表明 x 是一个只读变量的同时，x 还是一个值为 5 的常量，所以可以用来初始化 array 容器。

C++ 11标准中，为了解决 const 关键字的双重语义问题，保留了 const 表示“只读”的语义，而将“常量”的语义划分给了新添加的 constexpr 关键字。**因此 C++11 标准中，建议将 const 和 constexpr 的功能区分开，即凡是表达“只读”语义的场景都使用 const，表达“常量”语义的场景都使用 constexpr。**

```
在上面的实例程序中，dis_2() 函数中使用 const int x 是不规范的，应使用 constexpr 关键字。
```