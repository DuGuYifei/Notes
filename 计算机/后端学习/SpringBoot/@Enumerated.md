# @Enumerated

默认从0开始

```java
@Entity
public class User {
    //...
    @Enumerated(EnumType.ORDINAL)
    private Gender gender;
    //...
}
```

如果想不从0开始，需要[自定义](../../计算机语言/Java/Java知识积累/Enum.md)