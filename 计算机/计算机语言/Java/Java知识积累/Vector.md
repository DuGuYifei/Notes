# Vector

和ArrayList类似，但是Vector是线程安全的，因此在多线程环境下使用Vector比ArrayList更安全。

为什么线程安全？因为它的每个方法都被 synchronized 关键字修饰，即在多线程环境下，同一时刻只允许一个线程访问Vector对象的方法。这样可以避免多个线程同时修改Vector对象的状态，导致数据不一致或者其他问题。

