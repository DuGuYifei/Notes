# try-with-resources

```java
try (FileInputStream inputStream = new FileInputStream("file.txt")) {
    // 使用 inputStream 进行文件操作
} catch (IOException e) {
    // 处理异常
}
```

当 try 块执行结束时，会自动调用 [close()](close.md) 方法来关闭 inputStream 资源，即使发生异常也会被正确地关闭。

[finally](finally.md)