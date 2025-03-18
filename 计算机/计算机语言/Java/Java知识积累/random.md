# random

## Random和SecureRandom
SecureRandom提供了更高的随机性和密码学安全性。它使用更强大的随机算法和随机源来生成随机数，适用于需要高度安全性的场景。更慢，更安全。

而Random类生成的随机数是伪随机数，它使用简单的算法和种子来生成随机数序列。

## Random
1. 整数

```java
import java.util.Random;
Random r=new Random();
int number=r.nextInt(10);  // [0,10)
int number=r.nextInt(10)+1; // [1,11) (0,10]
```

2. 浮点数

```java
import java.util.Random;
Math.random(); // [0,1)
int x=(int)(Math.random()*100)+1 // [1,101) (0,100]
```

## SecureRandom



```java
import java.security.SecureRandom;

SecureRandom random = new SecureRandom();
byte bytes[] = new byte[20];
random.nextBytes(bytes); // 生成20个字节的安全随机数赋值到bytes中
int ran = random.nextInt(); // 生成一个随机整数
int ran = random.nextInt(100); // 生成一个0-100之间的随机整数
```