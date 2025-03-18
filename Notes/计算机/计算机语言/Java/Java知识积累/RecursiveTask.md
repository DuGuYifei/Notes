# RecursiveTask

## 1. 介绍

`RecursiveTask`是`ForkJoinTask`的子类，用于有返回值的任务。

## 2. 使用

```java
class Counter extends RecursiveTask<Integer>
{
	//...
	@Override
	protected Integer compute()
	{
		if (to - from < THRESHOLD)
		{
			//...
		}
		else
		{
			int mid = (from + to) / 2;
			Counter first = new Counter(values, from, mid, filter);
			Counter second = new Counter(values, mid, to, filter);
			// 方法1
			invokeAll(first, second);
			return first.join() + second.join();

			// 方法2
			first.fork();
			int result = second.compute();
			return first.join() + result;
		}
	}
}
```

## 3. 常用方法

### `compute()`

`compute()`方法是`RecursiveTask`的抽象方法，用于实现任务的逻辑。

### `fork()`

`fork()`方法用于异步执行任务。

### `join()`

`join()`方法用于获取任务的执行结果。

### `invokeAll()`

`invokeAll()`方法用于执行多个任务。