# MicroMeter

## 1. 介绍

Spring Boot 2.0引入了Micrometer，它是一个应用程序度量门面，旨在为Spring Boot，Atlas，Datadog，Graphite，Influx，JMX，New Relic，Prometheus，SignalFx，StatsD和Wavefront提供一种简单的方式。Micrometer还添加了对分布式跟踪系统的支持，包括Spring Cloud Sleuth，Zipkin和Brave。

## 2. 依赖
```xml
<dependency>
	<groupId>io.micrometer</groupId>
	<artifactId>micrometer-core</artifactId>
	<version>1.10.2</version>
</dependency>
```
下面这个是用于将数据发送到[Prometheus](./Prometheus.md)的依赖
```xml
<dependency>
	<groupId>io.micrometer</groupId>
	<artifactId>micrometer-registry-prometheus</artifactId>
	<version>1.1.0</version>
</dependency>
```

## 常用类
1. MeterRegistry
   1. 是一个注册表，用于注册各种类型的指标
2. Counter
   1. 计数器，用于计数
3. Gauge
   1. 仪表，用于记录某个值
4. Timer
   1. 计时器，用于记录某个方法的执行时间