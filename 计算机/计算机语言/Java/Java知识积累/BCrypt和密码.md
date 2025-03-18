# BCrypt和密码

## BCrypt

BCrypt是一个密码散列函数，基于Blowfish加密算法，由Niels Provos和David Mazières设计，于1999年发布。它的优点是易于使用，且可调节计算强度，使得攻击者必须做出权衡，才能破解密码。

BCrypt的计算强度由计算密度决定，计算密度越大，计算时间越长，破解难度越大。计算密度的单位是log2，取值范围是4~31，表示计算密度为2^4~2^31次方。默认值是10，表示计算密度为2^10次方。

## 依赖

```xml
		<dependency>
			<groupId>org.springframework.security</groupId>
			<artifactId>spring-security-crypto</artifactId>
			<version>5.7.4</version>
		</dependency>
```

## 常用函数

```java
import lsea.utils.RandomBase64Generator;

// 生成加密后的密码
String encryptedPassword = BCrypt.hashpw(
    	dto.getPassword(), // string 原密码
        BCrypt.gensalt()); // string 盐值：随机生成，盐值是指在计算散列值的时候，加入的一些随机字符串，使得即使两个用户的密码相同，其散列值也不同

public void changePassword(String oldPassword, String newPassword)
      throws GenericConflictError {
	// 验证原密码是否正确，oldPassword是用户输入的原密码，this.getPassword()是数据库中的加密的密码
    if (BCrypt.checkpw(oldPassword, this.getPassword())) {
    	this.setPassword(BCrypt.hashpw(newPassword, BCrypt.gensalt()));
    } else {
      	throw new GenericConflictError("Incorrect password");
    }
}
```