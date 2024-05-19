# shared_ptr

shared_ptr 是 C++ 标准库中的一种智能指针，用于自动管理动态分配的对象的生命周期。它是 std::shared_ptr 的全称，定义在 <memory> 头文件中。shared_ptr 通过引用计数来管理对象的内存，当最后一个引用被销毁时，shared_ptr 会自动释放所管理的对象的内存。

特点:
1. 引用计数：每个 shared_ptr 对象内部维护一个引用计数，表示有多少个 shared_ptr 实例共享同一个动态分配的对象。当引用计数变为零时，所管理的对象会被销毁。
2. 线程安全：shared_ptr 的引用计数操作是线程安全的，可以在多个线程中安全使用同一个 shared_ptr 实例。
3. 控制块：每个 shared_ptr 会和一个控制块相关联，控制块中存储了引用计数和对象的管理信息。


```cpp
std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
std::shared_ptr<MyClass> ptr2 = ptr1; // 共享同一个对象
```