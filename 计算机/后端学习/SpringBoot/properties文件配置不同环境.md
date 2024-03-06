# properties文件配置不同环境

1. application.properties

```properties
spring.profiles.active=dev # 可以改成其他的，会自动读取下面对应文件的配置
```

2. application-dev.properties

```properties
server.port=8081
```

3. application-prod.properties

```properties
server.port=8082
```

4. application-test.properties

```properties
server.port=8083
```

5. 获取环境
[Profile](Profile.md)
[多个main函数](../../计算机语言/Java/Java知识积累/多个main函数.md)

```java
Environment env = applicationContext.getEnvironment();
String[] activeProfiles = env.getActiveProfiles();
for (String profile : activeProfiles) {
	System.out.println("当前环境为：" + profile);
}
```

