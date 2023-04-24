# Hadoop命令运行jar

`hadoop jar filtercount-1.0-SNAPSHOT.jar package.name.FilterCount /user/adampap/WHV /user/lada16/lab3/q1-output`

在 Hadoop 中，-D 参数是用来设置配置项的，args 是命令行中除了 -D 参数之外的部分，通常是应用程序的参数。

new Configuration() 是在 Java 代码中创建一个 Hadoop 配置对象。这个对象可以用来读取和设置配置项，包括从命令行传入的 -D 参数和应用程序中使用的其他配置项。

```java
FileInputFormat.setInputPaths(job, new Path(args[0]));
FileOutputFormat.setOutputPath(job, new Path(args[1]));
```