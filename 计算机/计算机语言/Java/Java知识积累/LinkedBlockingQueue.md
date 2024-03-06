# LinkedBlockingQueue

## 介绍

`LinkedBlockingQueue`是一个基于链表实现的有界阻塞队列，它的内部实现和`LinkedBlockingDeque`类似，只是它只能从队列的头部取元素，从尾部插入元素。

作用是：在多线程环境下，用于任务调度，任务队列的实现。

比如：[生产者消费者](../../../%E5%88%86%E5%B8%83%E5%BC%8F%E5%A4%84%E7%90%86%E5%92%8C%E5%A4%9A%E7%BA%BF%E7%A8%8B/Producer-Consumer.md)
生产者可以将数据入队，消费者可以从队列中取出数据。 如果队列为空，消费者将阻塞直到有新数据可用；如果队列已满，生产者将阻塞直到有可用空间。

## 代码示例

```java
public class LinkedBlockingQueueTest {
	public static void main(String[] args) throws InterruptedException {
		LinkedBlockingQueue<Integer> queue = new LinkedBlockingQueue<>(2);
		queue.put(1);
		queue.put(2);
		System.out.println(queue.take());
		System.out.println(queue.take());
	}
}
```