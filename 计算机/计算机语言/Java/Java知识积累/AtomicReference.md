# AtomicReference

[无锁操作](无锁操作.md)

## 讲解
用于对单个引用变量进行原子操作。它确保对引用执行的操作是原子的，即线程安全的，并且可以在并发编程中安全使用。

## 案例

```java
public class AtomicReferenceTest {
	public static void main(String[] args) {
		AtomicReference<People> atomicReference = new AtomicReference<>();
		People people = new People("张三", 18);
		atomicReference.set(people);
		System.out.println(atomicReference.get());
		System.out.println(atomicReference.compareAndSet(people, new People("李四", 20)));
		System.out.println(atomicReference.get());
	}
}
```