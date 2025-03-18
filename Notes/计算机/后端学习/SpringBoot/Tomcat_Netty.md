# Tomcat_Netty

## 介绍
Tomcat一般用于部署Web应用程序，支持Servlet和JSP技术，提供了完整的Java Web容器功能。当我们使用Spring Boot或其他Java Web框架开发Web应用程序时，如果要在本地运行测试或调试，可以使用Spring Boot内置的Tomcat服务器来启动应用程序。

Netty则是一种基于事件驱动和异步非阻塞I/O模型的网络框架，可以用于构建高性能的网络服务器和客户端应用程序。相比于Tomcat，Netty更适合处理高并发、高吞吐量的网络通信任务。当我们需要开发基于TCP或UDP协议的自定义网络应用程序时，可以考虑使用Netty。

## Tomcat
Spring Boot默认使用的Web服务器是嵌入式的Tomcat，因此当我们使用Spring Boot Web Starter时，就默认包含了Tomcat作为Web容器。当然，我们也可以通过修改配置文件的方式，将Web服务器替换为其他支持的服务器，比如Jetty、Undertow等。

## Netty
Netty通常用于开发高性能的网络应用程序，比如网络服务器、代理服务器等。在Spring Boot中，如果我们需要使用Netty作为Web服务器，可以使用Spring Boot WebFlux Starter，它是基于Spring Framework 5和Reactor的反应式编程模型来实现Web编程。WebFlux Starter默认使用Netty作为Web服务器，也支持使用Undertow作为Web服务器。但需要注意的是，与传统的Spring MVC相比，WebFlux是一种完全不同的编程模型，需要我们采用异步的方式进行编程。

默认情况下 spring-cloud-starter-gateway 使用的是 Netty 服务器。可以在 application.properties 或 application.yml 中设置 spring.cloud.gateway.server 属性来指定使用其他的服务器，例如：

```properties
spring:
  cloud:
    gateway:
      server:
        port: 8080
        engine: # 指定服务器引擎
          netty: # 使用 Netty 服务器
            enabled: true
          tomcat: # 使用 Tomcat 服务器
            enabled: false
```

## 其他
除了Tomcat和Netty，还有一些其他的常用服务器，例如：

1. Jetty：Jetty是另一个流行的开源Java Servlet容器，与Tomcat类似。Jetty的特点是轻量级、快速启动和嵌入式部署。
2. Undertow：Undertow是一个高度灵活且性能卓越的Web服务器，它是Red Hat的开源项目之一。与Tomcat和Jetty不同，Undertow的设计目标是作为嵌入式服务器。
3. Apache HTTP Server：Apache HTTP Server是一个开源的Web服务器软件，它是在Apache许可证下发布的。它可以在多种操作系统上运行，并支持各种模块，例如PHP、Perl和Python等。
