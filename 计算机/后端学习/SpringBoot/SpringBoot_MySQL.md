# SpringBoot_MySQL

[JDBC_mysql](../../计算机语言/Java/Java知识积累/JDBC_mysql.md)

## configuration.property
```configuration
spring.datasource.url=jdbc:mysql://mysql57/pet?allowPublicKeyRetrieval=true&characterEncoding=UTF-8&useSSL=false&useUnicode=true&serverTimezone=UTC
spring.datasource.username=root
spring.datasource.password=root

spring.jpa.show-sql=true
spring.jpa.generate-ddl=true

server.port=8082
```

### spring.jpa.show-sql
会打印sql语句

### spring.jpa.generate-ddl
JPA可以根据我们定义的@Entity实体类,来自动生成表结构。在SpringBoot+JPA项目中, 我们可以通过定义属性spring.jpa.generate-ddl的值来控制这种行为。