# semaphores

## 介绍

信号量是一种特殊的变量，用于保护对共享资源的访问。信号量的值是一个非负整数，当一个线程访问共享资源时，它必须先获得信号量。如果信号量的值大于0，那么线程可以访问共享资源，并且信号量的值减1。如果信号量的值为0，那么线程必须等待，直到信号量的值大于0。当线程访问完共享资源后，它必须释放信号量，这会使信号量的值加1。如果有其他线程正在等待信号量，那么等待的线程中的一个会被唤醒，使它可以访问共享资源。

When a thread want to access shared resource, it must get semaphore firstly.

We can use wait() (P opearation -1) and signal() (V operation +1) to implement semaphore.

[P_V操作](P_V操作.md) 中有详细的介绍.

## types

### Generic Semaphore (通用信号量) / Counting Semaphore (计数信号量)

具有任何非负整数计数

### Binary Semaphore (二进制信号量)

具有值0或1的信号量

### Named Semaphore (命名信号量)

具有名称的信号量，可以在不同进程之间共享

使用命名信号量时，需要指定信号量的名称，以便其他进程可以访问它。如果信号量不存在，则会创建一个新的信号量。如果信号量已经存在，则会打开该信号量。证明有权限的条件是：信号量的所有者的有效用户ID等于调用进程的有效用户ID，或者信号量的所有者的有效组ID等于调用进程的有效组ID。

### Reader-Writer Semaphore (读写信号量)

Reader-Writer Semaphores: Reader-writer semaphores are used to manage shared resources that have both readers and writers. They allow multiple readers to access the resource concurrently while ensuring exclusive access for writers.

读写器信号量：读写器信号量用于管理同时拥有读写器的共享资源。 它们允许多个读者同时访问资源，同时确保作者的独占访问。