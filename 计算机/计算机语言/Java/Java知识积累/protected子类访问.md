# protected子类访问

1. 子类与父类在同一包中：被声明为 protected 的变量、方法和构造器能被同一个包中的任何其他类访问
2. 子类与父类不在同一包中：在子类中，子类实例可以访问其从基类继承而来的 protected 方法，但是不能访问父类实例的protected方法。

比如 [clone](clone.md) 中的`protected Object clone() throws CloneNotSupportedException`，如果不重写，那么子类即Object的子类是不能调用Object.clone()的，因为不在一个包。
