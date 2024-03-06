# JJwts_JWT创建和验证

## JWT

JWT是JSON Web Token的缩写，是一种基于JSON的开放标准（RFC 7519），用于在各方之间作为JSON对象安全地传输信息。主要用来在身份提供者和服务提供者间传递被认证的用户身份信息，以便于从资源服务器获取资源。

## JWT的结构

[Token](../../../服务器网络/域名和网址以及超文本传输协议/cookie_session_token.md)

## 依赖

```xml
		<dependency>
			<groupId>io.jsonwebtoken</groupId>
			<artifactId>jjwt</artifactId>
			<version>0.9.1</version>
		</dependency>
```

## 常用函数

```java
import io.jsonwebtoken.Jwts;

private static String temporarySecret = RandomBase64Generator.generateLong();

public String getJwtToken() {
    Date now = new Date();
	// 从环境变量中获取JWT_SECRET，如果没有则使用随机生成的临时密钥
    String secret = System.getenv("JWT_SECRET");
    if (secret == null) {
      secret = temporarySecret;
    }

    return Jwts
        .builder()
		// 设置JWT的id, 用于防止重放攻击
        .setId(UUID.randomUUID().toString())
		// 设置JWT的主题，在payload中存储用户的id
        .setSubject(id.toString())
		// 设置JWT的签发时间
        .setIssuedAt(now)
		// 设置JWT的过期时间
        .setExpiration(new Date(now.getTime() + 86400000)) // 24 hours
		// 设置JWT的签发者
        .signWith(SignatureAlgorithm.HS256, secret)
        .compact();
}

public static UUID verifyToken(String token) throws GenericForbiddenError {
    String secret = System.getenv("JWT_SECRET");
    if (secret == null) {
	    secret = temporarySecret;
    }
    try {
      	Claims claims = Jwts
        	.parser()
          	.setSigningKey(secret)
          	.parseClaimsJws(token)
          	.getBody();
      	return UUID.fromString(claims.getSubject());
    } catch (Exception e) {
      	throw new GenericForbiddenError("Invalid token");
    }
}
```

