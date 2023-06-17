# Semaphore

```java
import java.util.concurrent.Semaphore;

public class SemaphoreExample {
    public static void main(String[] args) {
        Semaphore semaphore = new Semaphore(2); // 初始化信号量为2

        // 创建线程并启动
        for (int i = 1; i <= 5; i++) {
            Thread thread = new Thread(new Worker(semaphore, i));
            thread.start();
        }
    }

    static class Worker implements Runnable {
        private Semaphore semaphore;
        private int id;

        public Worker(Semaphore semaphore, int id) {
            this.semaphore = semaphore;
            this.id = id;
        }

        @Override
        public void run() {
            try {
                semaphore.acquire(); // 获取许可
                System.out.println("Worker " + id + " is working");
                Thread.sleep(2000); // 模拟工作时间
                System.out.println("Worker " + id + " has finished working");
                semaphore.release(); // 释放许可
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
```