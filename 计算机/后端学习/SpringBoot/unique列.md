# unique列

[使用 spring boot jpa 的坑（unique 不起作用）](https://www.jianshu.com/p/053ad9ff4a8a)

[unique](../../数据库/SQL/unique.md)

```java

@Entity
@EntityListeners(AuditingEntityListener.class)
@Data
public class AdminUser {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(unique = true, nullable = false)
    // @NotEmpty
    // @Length(min = 4, max = 20)
    // @ApiModelProperty("账户名（4-20）")
    private String acctName;

    @Column
    // 转成32位 md5密码
    private String password;
}

```

String 对象需要加上length限制，max key length is 767 bytes

```java
    @Column(unique = true, nullable = false, length = 20)
    private String acctName;
```


