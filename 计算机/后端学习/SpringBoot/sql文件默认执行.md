# sql文件默认执行

在`src/main/resources`下新建`data.sql`文件和`schema.sql`，会默认执行

在 application.properties 或 application.yml 文件中添加以下配置：
```properties
spring.datasource.initialization-mode=never
```

这样 Spring Boot 就不会自动执行 `classpath:/schema.sql` 和 `classpath:/data.sql` 文件了。

