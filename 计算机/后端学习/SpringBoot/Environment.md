# Environment

Environment类是Spring Framework中的一个接口，它代表了应用程序的运行环境。通过Environment接口，可以获取应用程序的配置、属性、激活的profile以及其他与环境相关的信息。

## 0. 指定配置环境

* [在properties里指定环境，然后会自动读取对应properties](properties文件配置不同环境.md)

* 默认spring会使用application.properties作为配置文件，我们可以指定配置文件的位置，比如：

```properties
# 指定配置文件的位置
spring.config.location=classpath:/config/application.properties
```

也可以使用命令行参数指定配置文件的位置，比如：

```shell
java -jar xxx.jar --spring.config.location=classpath:/config/application.properties
```

也可以直接命令行添加配置，比如：

```shell
java -jar xxx.jar --spring.config.name=myapp
```

## 1. 获取Environment

```java
// 获取Environment
Environment environment = applicationContext.getEnvironment();
```

## 2. 获取配置文件中的值

```java
// 获取配置文件中的值
String name = environment.getProperty("name");
```

## 3. 获取激活的profile

```java
// 获取激活的profile
String[] profiles = environment.getActiveProfiles();
```

## 4. 获取所有的profile

```java
// 获取所有的profile
String[] profiles = environment.getDefaultProfiles();
```

## 5. 判断是否是某个profile

```java
// 判断是否是某个profile
boolean flag = environment.acceptsProfiles("dev");

// 判断是否是某个profile
Profile profile = Profile.of("dev", "test");
boolean flag = environment.acceptsProfiles(profile);
```

## 6. 获取当前环境

```java
// 获取当前环境
String env = environment.getProperty("spring.profiles.active");
```


