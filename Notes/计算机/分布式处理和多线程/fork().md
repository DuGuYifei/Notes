# fork()

[fork](../%E8%AE%A1%E7%AE%97%E6%9C%BA%E8%AF%AD%E8%A8%80/C/C%E7%9F%A5%E8%AF%86%E7%A7%AF%E7%B4%AF/fork.md)

## 介绍

fork 是一个系统调用，i.e. system call. Used to create a new process by **duplicating** the calling process. The new process is referred to as the child process.

The status are same when created, including code, data, stack and file descriptors. They will have different PID(进程标识符)。子进程是父进程的一个副本。并发执行。

父进程fork()返回子进程PID，子进程fork()返回0，如果出错返回-1。

在fork()系统调用的实现中，操作系统首先为子进程创建一个新的进程控制块（Process Control Block，PCB），复制父进程的PCB信息。然后，父进程的虚拟地址空间被复制到子进程的虚拟地址空间，包括代码、数据和堆栈。文件描述符表也会被复制，使得子进程能够继续访问父进程打开的文件。