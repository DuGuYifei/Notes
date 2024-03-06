# resource里执行sql
## init mode

1. 新版本的init mode:

```yaml
spring:
  sql:
    init:
      mode: always
```

2. 旧版本的init mode:

```yaml
spring.datasource.initialization-mode: always
```

上述有三种值：ALWAYS,EMBEDDED,NEVER，默认是embedded即内存数据库才执行

## 执行顺序

```yaml
defer-datasource-initialization: true
```

可以让sql在等待entity初始化数据库后再执行，不然先执行sql会报错。

## 完整案例

```yaml
spring:
  servlet:
    multipart:
      max-file-size: 11MB
      max-request-size: 11MB
  sql:
    init:
      mode: always
  datasource:
    url: jdbc:mysql://localhost:3306/ysxz?useSSL=false&serverTimezone=UTC
    username: root
    password:
    driver-class-name: com.mysql.cj.jdbc.Driver
  jpa:
    generate-ddl: true
    hibernate:
      ddl-auto: update
    properties:
      hibernate:
        dialect: org.hibernate.dialect.MySQL8Dialect
        format_sql: true
        show_sql: true
        auto_quote_keyword: true
    defer-datasource-initialization: true
```