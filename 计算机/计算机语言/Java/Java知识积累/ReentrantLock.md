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