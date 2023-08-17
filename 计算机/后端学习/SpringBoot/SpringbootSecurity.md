# Springboot Security

## 三个包

```xml
<dependencies>
    <!--常用的密、解密、哈希算法、数字签名等-->
    <dependency>
        <groupId>org.springframework.security</groupId>
        <artifactId>spring-security-crypto</artifactId>
    </dependency>
    <!--RSA加密-->
    <dependency>
        <groupId>org.springframework.security</groupId>
        <artifactId>spring-security-rsa</artifactId>
    </dependency>
    <!--bom是一个管理依赖版本的特殊的pom文件-->
    <dependency>
        <groupId>org.springframework.security</groupId>
        <artifactId>spring-security-bom</artifactId>
    </dependency>
<denpendencies>
```

## crypto使用
[crypto使用](../../计算机语言/Java/Java知识积累/BCrypt和密码.md)