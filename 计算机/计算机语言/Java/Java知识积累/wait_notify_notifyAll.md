# wait_notify_notifyAll

## wait

wait()方法是Object类的方法，它的作用是使当前执行代码的线程进行等待，wait()方法是有条件等待的，必须要在[synchronized](synchronized.md)同步块或者同步方法中调用wait()方法，否则会在运行时抛出IllegalMonitorStateException异常，因为只有在同步方法或者同步块中才能拥有对象的锁，而调用wait()方法的前提是当前线程已经拥有了该对象的锁，否则会抛出IllegalMonitorStateException异常。

wait()方法有一个重载的版本，可以指定等待的时间，即wait(long timeout)方法，如果在指定的时间内，线程还没有被notify()唤醒，那么线程会自动醒来继续执行。

**在synchronized代码块中，线程执行到结束或者调用了wait()方法时会自动释放锁，同时也会自动将当前线程挂起，直到有其他线程调用了相应对象的notify()或notifyAll()方法来唤醒该线程。**

## notify

notify()方法也是Object类的方法，它的作用是唤醒在此对象监视器上等待的单个线程，如果所有线程都在此对象上等待，则会选择唤醒其中一个线程。需要注意的是，选择哪个线程是随机的，也就是说，JVM会从所有等待线程中随机挑选一个唤醒，因此，如果有多个线程都在等待同一个对象，那么唤醒的线程是不确定的，有可能每次唤醒的线程都不一样。

notify()方法也有一个重载的版本，即notifyAll()方法，它的作用是唤醒在此对象监视器上等待的所有线程。

## notifyAll

notifyAll()方法是Object类的方法，它的作用是唤醒在此对象监视器(monitor)上等待的所有线程。

## 使用wait,notify和notifyall的示例

在这个示例中，有一个Message类，用于存储消息。Sender类向Message中设置消息，并使用notify方法通知等待线程。Receiver类等待消息，并使用wait方法暂停线程的执行，直到有消息到达。当收到"exit"消息时，Sender使用notifyAll方法通知所有等待线程退出。

```java
public class WaitNotifyExample {
    public static void main(String[] args) throws InterruptedException {
        Message message = new Message("");

        Thread senderThread = new Thread(new Sender(message));
        Thread receiverThread1 = new Thread(new Receiver(message));
        Thread receiverThread2 = new Thread(new Receiver(message));

        senderThread.start();
        receiverThread1.start();
        receiverThread2.start();

        senderThread.join();
        receiverThread1.join();
        receiverThread2.join();
    }

    static class Sender implements Runnable {
        private Message message;

        public Sender(Message message) {
            this.message = message;
        }

        public void run() {
            String[] messages = {"Message 1", "Message 2", "Message 3"};

            for (String msg : messages) {
                message.setMessage(msg);

                synchronized (message) {
                    message.notify(); // 唤醒等待线程
                }

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            message.setMessage("exit");

            synchronized (message) {
                message.notifyAll(); // 唤醒所有等待线程
            }
        }
    }

    static class Receiver implements Runnable {
        private Message message;

        public Receiver(Message message) {
            this.message = message;
        }

        public void run() {
            while (true) {
                synchronized (message) {
                    try {
                        message.wait(); // 等待消息
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }

                    String msg = message.getMessage();

                    if (msg.equals("exit")) {
                        break;
                    }

                    System.out.println("Received message: " + msg);
                }
            }
        }
    }

    static class Message {
        private String message;

        public Message(String message) {
            this.message = message;
        }

        public String getMessage() {
            return message;
        }

        public void setMessage(String message) {
            this.message = message;
        }
    }
}
```