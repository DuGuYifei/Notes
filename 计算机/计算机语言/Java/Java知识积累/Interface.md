# Interface

```java
// 定义一个计算器接口
public interface Calculator {
    int add(int x, int y);
    int subtract(int x, int y);
}

// 实现一个具体的计算器类
public class BasicCalculator implements Calculator {
    @Override
    public int add(int x, int y) {
        return x + y;
    }

    @Override
    public int subtract(int x, int y) {
        return x - y;
    }
}
```