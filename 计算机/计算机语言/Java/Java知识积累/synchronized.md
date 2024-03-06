# synchronized

[线程锁](线程锁.md)

[锁升级](锁升级.md)

## 作用

synchronized 用于修饰方法或者代码块，作用是保证线程安全。

在Java中，每个对象都有一个关联的**监视器锁（monitor lock）**，可以**用synchronized关键字来获取该锁**。当一个线程获取了锁，其他线程就无法访问该锁所保护的代码块，直到该线程释放锁。

synchronized关键字只是一种**语法糖**，其底层实现是基于对象头中的标志位来实现的。因此，所有的Java对象都拥有监视器锁、wait()方法和notify()方法等。这些方法是由Java虚拟机提供的，用于实现线程间的协作和通信。

**在synchronized代码块中，线程执行到结束或者调用了wait()方法时会自动释放锁，同时也会自动将当前线程挂起，直到有其他线程调用了相应对象的notify()或notifyAll()方法来唤醒该线程。**

[wait_notify_notifyAll](wait_notify_notifyAll.md)

## 原理

synchronized 是通过对象的 monitor 来实现的，每个对象都有一个 monitor，当一个线程访问对象的 synchronized 方法或者代码块时，就会获取对象的 monitor，当线程访问完后，会释放对象的 monitor。


## 修饰方法

当一个线程访问 synchronized 修饰的方法时，其他线程无法访问该方法，直到该线程访问完毕。

```java
public class SynchronizedTest {
	public synchronized void test() {
		System.out.println("test");
	}
}
```

## 修饰代码块

当一个线程访问 synchronized 修饰的代码块时，其他线程无法访问该代码块，直到该线程访问完毕。

```java
public class SynchronizedTest {
	public void test() {
		synchronized (this) {
			System.out.println("test");
		}
	}
}
```