# CritialSection

## 介绍

Critial Section是一种**同步机制，用于保护共享资源**，使得多个线程可以安全的访问共享资源。中文是临界区，也叫临界段。


同步多个进程或线程，保护共享资源不被同时访问的代码块称为临界区。

The code block that synchronizes multiple processes or threads to protect shared resources from simultaneous access is called a critical section.

## 哪些资源属于临界资源
1. 全局变量
2. 静态变量
3. 动态分配的内存
4. 文件
5. 数据库
6. 硬件资源
7. 网络资源
8. 打印机
9. 缓冲区
10. 共享变量
11. 共享数据结构

不是临界资源：静态常量，因为虽然全局但是只读。