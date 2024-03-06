# finally


finally 是 Java 中的一个关键字，用于定义一个代码块，在 try 或 catch 块中的代码执行完毕后，无论是否发生异常，都会执行该代码块。

finally 块通常用于释放资源或执行一些清理操作，例如关闭文件、关闭数据库连接、释放锁等。在 finally 块中的代码总是会被执行，即使在 try 或 catch 块中遇到了异常或者 return 语句等控制流语句。

以下是一个使用 finally 块的示例：

```java
try {
    // 执行一些可能会抛出异常的代码
} catch (Exception e) {
    // 处理异常
} finally {
    // 释放资源或执行清理操作
}
```