# volatile

## 作用

volatile 修饰的变量，保证了可见性，但不保证原子性。不同线程之间的可见性，确保一个线程对变量的修改对其他线程可见。

## 原理

volatile 修饰的变量，每次使用前，都会从主内存中读取最新的值，而不是从工作内存中读取。当线程修改了变量的值后，会立即刷新到主内存中。

## 代码示例

```java
public class VolatileTest {
	private volatile int count = 0;

	public void test() {
		count++;
	}
}
```