# Timer

```java
public class MyTask extends TimerTask
{

    @Override
    public void run()
    {
        SimpleDateFormat sdf = null;
        sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
        System.out.println("当前时间：" + sdf.format(new Date()));
        
    }
    
}
```

```java
public class TestTask
{
    public static void main(String[] args)
    {
        Timer t = new Timer(); // 建立Timer对象
        MyTask task = new MyTask(); //定义任务
        t.schedule(task, 1000, 2000);//设置任务的执行，1秒后开始，每2秒执行一次
        
        Calendar cal = Calendar.getInstance(); // 定义日期对象
        cal.set(Calendar.MINUTE, 30); // 设置日期的分钟数
        
        t.schedule(task, cal.getTime() , 2000); // 指定的时间开始执行，每2秒执行一次
    }
}
```