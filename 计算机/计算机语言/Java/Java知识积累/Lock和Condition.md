# Lock和Condition

## 介绍
Lock 接口是 synchronized 关键字的替代品，它提供了比 synchronized 更精细的锁机制。Lock 接口提供了可重入锁和公平锁的支持，允许线程在获取锁失败时进行等待或者超时，同时也提供了更好的性能和可伸缩性。

Condition 接口是 Object 类的 wait、notify 和 notifyAll 方法的替代品，它可以与任意 Lock 对象一起使用。通过 Condition 接口，可以实现线程的等待和唤醒，从而更灵活地控制线程同步。与 wait 和 notify 方法相比，Condition 接口提供了更加安全和可靠的线程同步机制。


## await() 和 signal() 和 signalAll() 方法
await()、signal() 和 signalAll() 是 Condition 接口提供的三个重要方法，用于线程的等待和唤醒。

await() 方法用于让当前线程等待，直到其他线程调用该条件变量的 signal() 或 signalAll() 方法来唤醒它。在调用 await() 方法之前，必须先获得与该条件变量相关联的锁，否则会抛出 IllegalMonitorStateException 异常。在当前线程等待时，它会释放掉该锁，使其他线程能够获得锁并执行相应的操作。

signal() 方法用于唤醒一个正在等待该条件变量的线程。在调用 signal() 方法之前，必须先获得与该条件变量相关联的锁，否则会抛出 IllegalMonitorStateException 异常。被唤醒的线程会重新尝试获得锁，并继续执行它被唤醒前所阻塞的代码。

signalAll() 方法用于唤醒所有正在等待该条件变量的线程。在调用 signalAll() 方法之前，必须先获得与该条件变量相关联的锁，否则会抛出 IllegalMonitorStateException 异常。所有被唤醒的线程都会重新尝试获得锁，并继续执行它们被唤醒前所阻塞的代码。

使用 await()、signal() 和 signalAll() 方法可以实现更加灵活的线程同步。例如，在生产者-消费者模型中，可以使用条件变量来实现缓冲区的阻塞和唤醒操作，从而实现生产者和消费者之间的同步。

### 解答问题
如果有多个线程在同一个条件变量上等待，当另外一个线程调用该条件变量的 signal() 方法时，只会唤醒其中一个线程，并且唤醒的线程是不确定的，可能是等待时间最长的那个线程，也可能是随机选择的某个线程。唤醒的线程将尝试重新获取锁，并从之前被阻塞的地方继续执行代码。

如果调用 signalAll() 方法，则会唤醒所有正在等待该条件变量的线程，它们会同时竞争锁，然后从之前被阻塞的地方继续执行代码。因此，在使用 signal() 和 signalAll() 方法时，需要考虑到线程唤醒的顺序和并发性问题。

## 示例
```java
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BoundedBuffer {
    final Lock lock = new ReentrantLock();
    final Condition notFull = lock.newCondition();
    final Condition notEmpty = lock.newCondition();

    final Object[] items = new Object[100];
    int putptr, takeptr, count;

    public void put(Object x) throws InterruptedException {
        lock.lock();
        try {
            while (count == items.length)
                notFull.await();
            items[putptr] = x;
            if (++putptr == items.length) putptr = 0;
            ++count;
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }

    public Object take() throws InterruptedException {
        lock.lock();
        try {
            while (count == 0)
                notEmpty.await();
            Object x = items[takeptr];
            if (++takeptr == items.length) takeptr = 0;
            --count;
            notFull.signal();
            return x;
        } finally {
            lock.unlock();
        }
    }
}
```