# MutualExclusion


## 介绍
Multual Exclusion 意思是互斥。在分布式系统中，多个进程或者线程同时访问一个共享资源，会导致数据不一致的问题。为了解决这个问题，需要对共享资源进行互斥访问。


i.e. mutex.

确保一次只有一个线程或进程可以访问共享资源或临界区的机制。 

A machanism to ensure that only one process at a time accesses a shared resource or critical section.

It provides mutual exclusion or exclusive access to a particular resource, allowing for synchronized and orderly access.

## 实现方式

1. 信号量 semaphores
2. 互斥锁 mutex lock
3. 读写锁 read-write lock
4. 互斥标志 mutex flag
5. 管程 monitor