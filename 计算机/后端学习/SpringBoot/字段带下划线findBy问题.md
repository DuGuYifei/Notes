# 字段带下划线findBy问题

当使用`findBy`时会被下划线分开，所以需要：

```java
@Column(name="user_name")
private String username;
```