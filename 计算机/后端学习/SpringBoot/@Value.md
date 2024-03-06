# @Value

`@Value`注解可以用来获取配置文件中的值，比如：

```properties
# application.properties
name=张三
num=123
```

```java
// 获取配置文件中的值
@Value("${name}")
private String name;

@Value("${num}")
private int num;
```

