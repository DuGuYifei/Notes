# Integer缓存

## 介绍
Integer 有一个缓存，范围是 -128 到 127，超过这个范围就会新建一个对象。

它每次调用都会使用valueOf方法，这个方法会判断是否在缓存范围内，如果在就直接返回缓存中的对象，否则就新建一个对象。

```java
public static Integer valueOf(int i) {
	if (i >= IntegerCache.low && i <= IntegerCache.high)
		return IntegerCache.cache[i + (-IntegerCache.low)];
	return new Integer(i);
}
```

## 案例

```java
import java.lang.reflect.Field;

public class IntegerCacheTest {
	public static void main(String[] args) {
		Integer a = 2;
		Integer b = 2;
		Integer c = 1000;
		Integer d = 1000;

		System.out.println(a == b); // true
		System.out.println(c == d); // false
	}
}
```

