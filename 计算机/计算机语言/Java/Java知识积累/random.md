# random

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