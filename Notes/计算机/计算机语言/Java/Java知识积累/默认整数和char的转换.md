# 默认整数和char的转换

```java
StringBuilder ans= new StringBuilder();
while (res > 0) {
	ans.append(res&1);
	res >>= 1;
}
```

注意上面用的是`res&1`，而不是`(res&1) + '0'`，因为java会直接将数字转换为char不用ascii码。

但是强转为char的时候，会将数字转换为ascii码。
```java
System.out.println((char)97); // a
```