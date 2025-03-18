# finalize

finalize() 是 Java 中一个用于对象垃圾回收的方法。每个对象都有一个 finalize() 方法，当该对象即将被垃圾回收器回收时，该方法会被垃圾回收器调用。

finalize() 方法定义在 Object 类中，因此所有的类都继承了这个方法。该方法的默认实现是空的，因此如果一个类没有重写 finalize() 方法，那么该方法不会产生任何影响。

从 Java 9 开始，finalize() 方法已经被标记为过时方法，不推荐使用。建议使用 [try-with-resources](try-with-resources.md) 或类似的方法来确保资源得到释放。
