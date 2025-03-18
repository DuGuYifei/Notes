# AtomicInteger

[无锁操作](./无锁操作.md)

## 介绍

原子类是一种无锁操作，它是通过CAS操作来实现的。原子类可以保证多个线程对共享变量的操作是原子性的，因此可以保证线程安全。

## 使用

```java
// 创建原子类
AtomicInteger atomicInteger = new AtomicInteger(0);
// 获取原子类的值
int value = atomicInteger.get();
// 设置原子类的值
atomicInteger.set(1);
// 原子类的值加1
atomicInteger.incrementAndGet();
// 原子类的值减1
atomicInteger.decrementAndGet();
// 原子类的值加1
atomicInteger.getAndIncrement();
// 原子类的值减1
atomicInteger.getAndDecrement();
// 原子类的值加上指定的值
atomicInteger.addAndGet(1);
// 原子类的值减去指定的值
atomicInteger.addAndGet(-1);
// 原子类的值加上指定的值
atomicInteger.getAndAdd(1);
// 原子类的值减去指定的值
atomicInteger.getAndAdd(-1);
// 原子类的值与指定的值比较，如果相等则设置为指定的值
atomicInteger.compareAndSet(0, 1); // 如果原子类的值为0，则设置为1
```

get在前和在后的区别是：get在前是先获取并返回值，然后再进行操作；get在后是先进行操作，然后再获取并返回值。

