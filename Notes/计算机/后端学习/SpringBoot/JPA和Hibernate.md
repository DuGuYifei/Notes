# JPA和Hibernate

## 区别
JPA和Hibernate之间的主要区别在于JPA是一个规范，而Hibernate是Red Hat对JPA规范的实现。 只有一个JPA规范。 JPA规范通过Java社区进程（JCP）协同开发，更新作为Java规范请求（JSR）发布。 如果社区同意JSR中提出的所有更改，则会发布新版本的API。

## Hibernate
这里，spring.jpa.hibernate.ddl-auto可以是none、update、create或create-drop。有关详细信息，请参阅[Hibernate 文档](https://docs.jboss.org/hibernate/orm/5.4/userguide/html_single/Hibernate_User_Guide.html#configurations-hbmddl)。
* none: MySQL的默认值。没有对数据库结构进行任何更改。
* update: Hibernate 根据给定的实体结构改变数据库。
* create: 每次都创建数据库但不会在关闭时删除它。
* create-drop: 创建数据库并在SessionFactory关闭时删除它

