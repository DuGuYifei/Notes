# @Entity@Table

@Entity注解和@Table注解都是Java Persistence API中定义的一种注解。

如果同时使用了@Entity(name="student")和@Table(name="book")，最终对应的表名是book，这说明优先级：**@Table>@Entity**

## @Entity
1. @Entity说明这个class是实体类，并且使用默认的orm规则，即class名就是数据库表中表明，class字段名即表中字段名。@Entity注解指明这是一个实体Bean。

2. @Entity注解表示该类是要给实体类，在羡慕启动时会根据该类自动生成一张表，表的名称即@Entity注解中name的值，如果不配置name，默认表明为类名

3. 所有的实体类都要有主键，`@Id`注解表示该属性是一个主键，@GeneratedValue注解表示注解自动生成，strategy则表示主键的生成策略

4. 默认情况下，生成的表中字段的名称就是实体类中属性的名称，通过`@Column注解`可以定制生成的字段属性，name表示该属性对应的数据表中字段的名称，nullable表示该字段非空

5. [@Transient](@Transient.md)注解表示在生成数据库中的表时，该属性被忽略，即不生成对应的字段


## Table
1. @Table注解默认情况下只会完成表和实体之间的映射，声明才对象映射到数据库的数据表，通过它可以为实体指定表(table)

2. 常用属性：name  指定表

3. @Table(name = "book")

**@Table注解是一个非必须的注解**，@Table注解指定了Entity所要映射的数据库表，其中@Table.name()用来指定映射表的表名。


## Entity 涉及到的注解

1.   @Entity ：表明是一个实体类
2.   @Table ：对应的数据表名
3.   @Id ：主键
4.   [@GeneratedValue](@GeneratedValue.md)：主键生成策略
5.   @Column : 映射表对应的字段名
6.   [@Basic](@Basic.md) ： 表示该属性是表字段的映射。 如果实体的字段上没有任何注解默认就是@Basic
7.   [@Transient](@Transient.md) : 表示该属性不是表字段的映射
8.   @Lob : 将属性映射成支持的大对象类型 ，如Clob、Blob(例子：[@Basic](@Basic.md)里的例子是一个图片存在portrait列)
9.   @IdClass 联合主键，一般不用也不推荐用
10.  @Temporal :  用来设置Date类型的属性映射到对应精度的字段
11.  @Enumerated 直接映射枚举类型的字段6