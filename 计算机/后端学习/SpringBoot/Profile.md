# Profile

## 1. 什么是Profile

Profile是SpringBoot中的一个概念，它可以让我们在同一个工程中，配置不同的环境，比如开发环境，测试环境，生产环境等等。

## 2. 如何使用Profile

在不同application.properties中，我们可以配置不同的环境，比如：

```properties
# 开发环境
spring.profiles.active=dev
# 测试环境
spring.profiles.active=test
# 生产环境
spring.profiles.active=prod
```

## 3. 获取不同环境的配置

```java
// 获取当前环境
@Value("${spring.profiles.active}")
private String env;
```

## 4. 代码中使用不同环境的配置

```java
// 代码中使用不同环境的配置
if (env.equals("dev")) {
	// 开发环境
} else if (env.equals("test")) {
	// 测试环境
} else if (env.equals("prod")) {
	// 生产环境
}
```

## 5. 使用Profile类

```java
// 使用Profile类
Profile profile = applicationContext.getEnvironment().getActiveProfiles()[0];

Profile profile2 = Profile.of("dev", "test");
boolean flag = environment.acceptsProfiles(profile);

xxx.enable(flag);


if (profile.equals(Profile.DEV)) {
	// 开发环境
} else if (profile.equals(Profile.TEST)) {
	// 测试环境
} else if (profile.equals(Profile.PROD)) {
	// 生产环境
}
```



