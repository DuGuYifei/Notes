# emplace

在vector中`emplace_back`没有`push_back`快

最近在刷题的时候看别人优雅的代码，发现一个叫做“emplace”的新朋友，检索了网上的相关资料后知道，这是C++11中加入的新特性，`emplace_back`能通过参数构造对象，不需要拷贝或者移动内存，相比`push_back`能更好地避免内存的拷贝与移动，使容器插入元素的性能得到进一步提升。

由此，在大多数情况下应该优先使用`emplace_back`来代替`push_back`。所有的标准库容器（array除外，因为它的长度不可改变，不能插入元素）都增加了类似的方法：`emplace`、`emplace_hint`、`emplace_front`、`emplace_after`、`emplace_back`等.

[C++11中emplace的使用\_MaloFleur-CSDN博客\_emplace](https://blog.csdn.net/u013700358/article/details/52623985)
