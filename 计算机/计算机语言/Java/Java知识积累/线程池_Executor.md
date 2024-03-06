# 线程池_Executor


## 基本

### 固定size
```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

ExecutorService executor = Executors.newFixedThreadPool(poolSize);
executor.execute(new Runnable() {
    @Override
    public void run() {
        // 任务执行的代码
    }
});
executor.shutdown();
```

### dynamic size
```java
ExecutorService dynamicExecutor = new ThreadPoolExecutor(
    2, //minimum number of threads
    16, //maximum number of threads
    60, // maximum time of thread inactive state
    TimeUnit.SECONDS, // time unit of third parameter
    new LinkedBlockingQueue<Runnable>() //task queue to be used by threads
)

```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPoolExample {
    public static void main(String[] args) {
        int poolSize = 5;
        ExecutorService executor = Executors.newFixedThreadPool(poolSize);
        
        for (int i = 0; i < 10; i++) {
            executor.execute(new Runnable() {
                @Override
                public void run() {
                    System.out.println("Task executed by thread: " + Thread.currentThread().getName());
                }
            });
        }
        
        executor.shutdown();
    }
}
```

## submit()

1. 传递[Runnable or Callable](Runnable_Callable.md)对象给`ExecutorService`的`submit()`方法，可以将任务提交给线程池执行。
2. `Future<T>` object is returned by the `submit()` method.
   1. 它可以用于判断是否任务执行完毕
   2. `get()`方法可以等待完成并获取任务执行的结果（blocking function）
   3. `isDone()` 方法可以判断任务是否执行完毕
   4. `cancel()` 方法可以取消任务的执行

## 多任务判断结束

### `Runnable`和`CountDownLatch`
```java
import java.util.concurrent.CountDownLatch;

public class CountDownLatchExample {
    public static void main(String[] args) throws InterruptedException {
        int numThreads = 5;

        // 创建一个CountDownLatch，初始计数器值为5
        CountDownLatch latch = new CountDownLatch(numThreads);

        // 创建并启动多个线程执行任务
        for (int i = 0; i < numThreads; i++) {
            Thread thread = new Thread(() -> {
                // 执行任务
                System.out.println("Task executed by Thread " + Thread.currentThread().getId());

                // 任务执行完毕，递减计数器的值
                latch.countDown();
            });
            thread.start();
        }

        // 等待所有线程执行完毕
        latch.await();

        // 所有线程的任务执行完毕
        System.out.println("All tasks completed");
    }
}
```

### `Runnable`和`Future<>`
```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ThreadPoolExample {
    public static void main(String[] args) {
        int numTasks = 5;

        // 创建线程池
        ExecutorService executor = Executors.newFixedThreadPool(numTasks);

        // 提交任务并获取Future对象
        Future<?>[] futures = new Future[numTasks];
        for (int i = 0; i < numTasks; i++) {
            int taskId = i + 1;
            futures[i] = executor.submit(() -> {
                // 任务逻辑
                System.out.println("Task " + taskId + " executed");
            });
        }

        // 等待任务执行完成
        for (Future<?> future : futures) {
            try {
                future.get(); // 等待任务执行完成
            } catch (Exception e) {
                // 处理异常
            }
        }

        // 关闭线程池
        executor.shutdown();
    }
}
```

### `Callable<>` 和 `Future<>`
```java
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class ThreadPoolExample {
    public static void main(String[] args) {
        int numTasks = 5;
        
        // 创建线程池
        ExecutorService executor = Executors.newFixedThreadPool(numTasks);
        
        // 创建任务列表
        List<Callable<String>> tasks = new ArrayList<>();
        for (int i = 0; i < numTasks; i++) {
            int taskId = i + 1;
            tasks.add(() -> {
                // 任务逻辑
                String result = "Task " + taskId + " executed";
                Thread.sleep(1000); // 模拟任务执行时间
                return result;
            });
        }
        
        try {
            // 执行任务并等待全部完成
            List<Future<String>> futures = executor.invokeAll(tasks);
            
            // 获取任务结果
            for (Future<String> future : futures) {
                String result = future.get();
                System.out.println(result);
            }
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }
        
        // 关闭线程池
        executor.shutdown();
    }
}
```