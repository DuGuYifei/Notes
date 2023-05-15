# Serializable

这个接口用以实现序列化，跟tostring没关系，也不用重写什么，但是要保证
1. 类的所有属性都是可序列化的，否则会报错。
2. 类的所有父类都是可序列化的，否则会报错。

如果一定要重写，重写的是：

```java
private void writeObject(java.io.ObjectOutputStream out) throws IOException
private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
```
