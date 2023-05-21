# actuator

[SLS时序监控实战: Spring Boot应用监控最佳实践-阿里云开发者社区](https://developer.aliyun.com/article/770726)

可以提供信息用于监控和管理，比如健康检查、审计、统计和HTTP追踪等。

## 配置

```xml
		<dependency>
			<groupId>org.springframework.boot</groupId>
			<artifactId>spring-boot-starter-actuator</artifactId>
		</dependency>
```

```properties
management.metrics.tags.application=${spring.application.name}
management.endpoints.web.exposure.include=*
```

第二行是为了打开所有接口，不然默认只有health和info，详情见上面的链接。
