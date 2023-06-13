# Monitor

## 介绍

Monitor是一种同步机制，它允许线程互斥地访问一段代码，以实现线程间的通信。每个对象都有一个监视器锁（monitor lock），同时最多只有一个线程可以持有该锁。当线程获取监视器锁时，它就可以执行被该锁保护的代码。如果其他线程试图获取同一个锁，那么它就会被阻塞，直到第一个线程释放这个锁。

A Monitor is a synchronization mechanism that allows threads to access a section of code mutually exclusively, enabling inter-thread communication. Each object has a monitor lock, also known as a mutex lock or intrinsic lock, and at most, only one thread can hold this lock at a time. When a thread acquires the monitor lock, it gains the ability to execute the code protected by that lock. If other threads attempt to acquire the same lock, they will be blocked until the first thread releases the lock.

Ideally, the waiting list is a FIFO, but in certain implementations or scenarios, the order of unblocking and granting access to the monitor lock may not strictly follow a FIFO sequence. 