# ConditionVariables

Condition variables are synchronization primitives that are commonly used in concurrent programming to enable threads to efficiently wait for a specific condition to become true before proceeding with their execution. They are typically associated with a lock or mutex to ensure mutual exclusion and coordinated access to shared resources.

条件变量是同步原语，常用于并发编程，使线程能够在继续执行之前有效地等待特定条件变为真。 它们通常与锁或互斥锁相关联，以确保互斥和协调访问共享资源。

Threads can use condition variables to check if a condition is true and, if not, enter a waiting state until another thread signals that the condition has changed.

线程可以使用条件变量来检查条件是否为真，如果不为真，则进入等待状态，直到另一个线程发出条件已更改的信号。

Wait: A thread can call the wait operation on a condition variable when it wants to wait for a condition to be satisfied. The wait operation releases the associated lock or mutex and puts the thread to sleep until it is awakened by a signal or broadcast.

Signal: A thread can call the signal operation on a condition variable to wake up one of the threads that are waiting on that condition variable. The awakened thread will reacquire the associated lock or mutex and continue its execution.

Broadcast: A thread can call the broadcast operation on a condition variable to wake up all the threads that are waiting on that condition variable. All awakened threads will compete to reacquire the associated lock or mutex and continue their execution.

等待：当一个线程想要等待一个条件被满足时，它可以调用一个条件变量的等待操作。 等待操作释放关联的锁或互斥锁，并使线程进入睡眠状态，直到它被信号或广播唤醒。

信号：线程可以调用条件变量上的信号操作来唤醒正在等待该条件变量的线程之一。 被唤醒的线程将重新获取关联的锁或互斥量并继续执行。

广播：线程可以调用条件变量的广播操作来唤醒所有等待该条件变量的线程。 所有被唤醒的线程将竞争重新获取关联的锁或互斥锁**并继续执行。**