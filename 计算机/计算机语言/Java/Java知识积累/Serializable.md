# Serializable

## 序列化
这个接口用以实现序列化，跟tostring没关系，也不用重写什么，但是要保证
1. 类的所有属性都是可序列化的，否则会报错。
2. 类的所有父类都是可序列化的，否则会报错。

如果一定要重写，重写的是：

```java
private void writeObject(java.io.ObjectOutputStream out) throws IOException
private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
```

## 写入

1. class name
2. unique ID
3. flag set that describe serialization method
4. description of the class's fields

Secure Hash Algorithm (SHA) is used to "fingerprint"(翻译：指纹) the class.

## 新旧版本兼容

### serialver
load old finferprint, 比如用`serialver`

serialver是一个命令行工具，用于获取类的serialVersionUID。

### serialVersionUID

1. 如果不指定，会自动生成，但是不同的JDK版本生成的可能不一样，所以不推荐。
2. 如果指定，一定要保证不同版本的类的serialVersionUID一致，否则会报错。

```java
class Employee implements Serializable {
    public static final long serialVersionUID = -1814239825517340645L;
}
```

当你更新了类，比如增加了一个属性，但是不想让旧版本的程序报错，可以这样做：

```java
class Employee implements Serializable {
	public static final long serialVersionUID = -1814239825517340645L;
	private String name;
}
```

否则由于自动生成的serialVersionUID不一样，会报错。

### @Serial


作用是指定serialVersionUID，这样就不用手动指定了。

```java
import java.io.Serializable;
public class User implements Serializable {
    @Serial // 指定序列化版本号
    private static final long serialVersionUID = 1L;
    
    private String name;
    private int age;
    
    // 构造函数、getter和setter方法省略
}
```

## 反序列化
案例：
[udp](udp.md)

其他：
```java
ObjectInputStream in = new ObjectInputStream(new FileInputStream("employee.ser"));
Employee e = (Employee) in.readObject();
```
