# Runnable_Callable

## 不同点

1. `Runnable`没有返回值，`Callable`有返回值
2. `Runnable`不会抛出异常，`Callable`会抛出异常

## 使用

```java
public class MyRunnable implements Runnable {
    @Override
    public void run() {
        // 任务的逻辑代码
    }
}

// 使用Runnable创建新线程
Thread thread = new Thread(new MyRunnable());
thread.start();
```

```java
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class MyCallable implements Callable<String> {
    @Override
    public String call() throws Exception {
        // 任务的逻辑代码
        return "Hello, Callable!";
    }
}

// 使用Callable创建新线程
ExecutorService executorService = Executors.newSingleThreadExecutor();
Future<String> future = executorService.submit(new MyCallable());
// 获取任务的返回结果
String result = future.get();
executorService.shutdown();
```