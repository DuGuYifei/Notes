# @ElementCollection
## 介绍

```java
import javax.persistence.ElementCollection;
import javax.persistence.Entity;
import javax.persistence.EnumType;
import javax.persistence.Enumerated;

@Entity
public class MyClass {
    // ...

    @ElementCollection(targetClass = TeachingSubjectEnum.class)
    @Enumerated(EnumType.STRING) // 或者 EnumType.ORDINAL
    private List<TeachingSubjectEnum> goodSubjects;

    // getters and setters
}
```

在JPA实体中使用@ElementCollection注解来映射枚举列表（或任何其他类型的集合）时，JPA（例如Hibernate）会自动创建一个新的关联表来存储这些集合元素。这个新表是专门用来保存实体与集合元素之间的关系的。