# syncronized

synchronized 是 Java 中用于实现线程同步的关键字，可以用于修饰方法或代码块。

**当一个方法或代码块被 synchronized 修饰时，同一时刻只能有一个线程进入该方法或代码块，其他线程需要等待当前线程执行完成后才能进入。**

synchronized 可以用于保证线程安全，避免多个线程同时访问共享资源造成的问题，例如数据竞争和并发访问问题等。

需要注意的是，使用 synchronized 会降低程序的性能，因为同步代码块只能被一个线程执行，其他线程需要等待，会导致线程的阻塞和切换。为了避免性能问题，可以尽量减少同步块的范围，或者使用更高效的同步方式，例如 Lock和Condition 等。

## 修饰方法
```java
public class Counter {
    private int count;

    public synchronized void increment() {
        count++;
    }

    public synchronized int getCount() {
        return count;
    }
}
```

## 修饰代码块

当使用 synchronized 修饰代码块时，需要将需要同步的代码放在一个花括号内，并且在 synchronized 关键字后面跟上一个锁对象。**这个代码块看起来像是一个函数，但实际上它不是一个函数，而是一个代码块。**

```java
public class Counter {
    private int count;
    private Object lock = new Object();

    public void increment() {
        synchronized (lock) {
            count++;
        }
    }

    public int getCount() {
        synchronized (lock) {
            return count;
        }
    }
}
```

在这个示例中，increment 和 getCount 方法分别使用了一个共享的对象 lock 作为锁来保证线程安全。**只有持有 lock 对象的线程才能进入 synchronized 代码块中执行操作，其他线程需要等待。**