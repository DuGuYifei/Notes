# @Basic

@Basic： 表示该属性是表字段的映射。 如果实体的字段上没有任何注解默认就是@Basic

```java
    @Lob
    @Basic(fetch = FetchType.LAZY)
    @ToString.Exclude
    private byte[] portrait;
```