# ReentrantLock

## 基本方法

1. `lock()` 获取锁
2. `unlock()` 释放锁

```java
myLock.lock(); // a ReentrantLock object
try {
	//…
}
finally {
	myLock.unlock();
}
```

## 可重入性
可重入就和默认的synchronized使用的内置锁一样，可以在获取锁的时候再获取一次，然后和`semaphore`一样，释放锁的时候也要释放两次。

```java
import java.util.concurrent.locks.ReentrantLock;

public class ReentrantLockExample {
    private ReentrantLock lock = new ReentrantLock();

    public void outerMethod() {
        lock.lock(); // 第一次获取锁
        try {
            System.out.println("Outer method: Lock acquired");

            innerMethod(); // 调用内部方法，再次获取锁
        } finally {
            lock.unlock(); // 第一次释放锁
            System.out.println("Outer method: Lock released");
        }
    }

    public void innerMethod() {
        lock.lock(); // 第二次获取锁
        try {
            System.out.println("Inner method: Lock acquired");
            // 执行受锁保护的代码块
        } finally {
            lock.unlock(); // 第二次释放锁
            System.out.println("Inner method: Lock released");
        }
    }
}
```

## Condition
[Condition](Condition.md)


## 公平和非公平锁

在创建时：
```java
ReentrantLock lock = new ReentrantLock(true); // 公平锁
ReentrantLock lock = new ReentrantLock(false); // 非公平锁
```