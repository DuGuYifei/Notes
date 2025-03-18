# SpringBoot_MySQL

[JDBC_mysql](../../计算机语言/Java/Java知识积累/JDBC_mysql.md)

## configuration.property
### JPA
```properties
spring.datasource.url=jdbc:mysql://mysql57/pet?allowPublicKeyRetrieval=true&characterEncoding=UTF-8&useSSL=false&useUnicode=true&serverTimezone=UTC
spring.datasource.username=root
spring.datasource.password=root

spring.jpa.show-sql=true
spring.jpa.generate-ddl=true

server.port=8082
```

### Hibernate
官方:https://spring.io/guides/gs/accessing-data-mysql/
```properties
spring.jpa.hibernate.ddl-auto=update
spring.datasource.url=jdbc:mysql://${MYSQL_HOST:localhost}:3306/db_example
spring.datasource.username=springuser
spring.datasource.password=ThePassword
spring.datasource.driver-class-name=com.mysql.cj.jdbc.Driver
#spring.jpa.show-sql: true
```

这里，spring.jpa.hibernate.ddl-auto可以是none、update、create或create-drop。有关详细信息，请参阅[Hibernate 文档](https://docs.jboss.org/hibernate/orm/5.4/userguide/html_single/Hibernate_User_Guide.html#configurations-hbmddl)。
* none: MySQL的默认值。没有对数据库结构进行任何更改。
* update: Hibernate 根据给定的实体结构改变数据库。
* create: 每次都创建数据库但不会在关闭时删除它。
* create-drop: 创建数据库并在SessionFactory关闭时删除它。

您必须从`create`或`update`开始，因为您还没有数据库结构。 首次运行后，您可以根据程序要求将其切换为`update`或`none`。 当您想对数据库结构进行一些更改时，请使用`update`。

### spring.jpa.show-sql
会打印sql语句

### spring.jpa.generate-ddl
JPA可以根据我们定义的@Entity实体类,来自动生成表结构。在SpringBoot+JPA项目中, 我们可以通过定义属性spring.jpa.generate-ddl的值来控制这种行为。