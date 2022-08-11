# 互相引用的类怎么解决error

文件一
```cpp
class A;

class B {
    ...
}
```

文件二
```cpp
class B;

class A {
    ...
}
```