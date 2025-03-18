# 多个main函数

java多个main函数并不影响，完全可以自己选择调用哪个main函数开始执行。

下面两个main函数就是一个开发环境，一个生产环境，可以自己选择调用哪个main函数。[properties文件配置不同环境](../../../后端学习/SpringBoot/properties文件配置不同环境.md)
```java

甚至你还可以在里面放第二个应用，比如我当初的案例就是一个springboot项目里还加了client的ui项目。

```java
package lsea;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import static lsea.tcp.TCPServerFunctions.startServer;

/* Requirement 2.5 */
/**
 * Application main class.
 */
@SpringBootApplication
public class LaboratoryApplication {

  /**
   * Application main entry point. Starts Spring Boot application context.
   *
   * @param args command line arguments
   */
  public static void main(String[] args) {
    System.setProperty("spring.profiles.active", "dev");
    SpringApplication.run(LaboratoryApplication.class, args);

    // Start the TCP server
    startServer();
  }
}
```

```java
package lsea;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import static lsea.tcp.TCPServerFunctions.startServer;

/* Requirement 2.5 */
/**
 * Application main class for production environment.
 */
@SpringBootApplication
public class ProductionApplication {

  /**
   * Application main entry point. Starts Spring Boot application context.
   * (Production Environment)
   *
   * @param args command line arguments
   */
  public static void main(String[] args) {
    System.setProperty("spring.profiles.active", "prod");
    SpringApplication.run(LaboratoryApplication.class, args);

    // Start the TCP server
    startServer();
  }
}
```