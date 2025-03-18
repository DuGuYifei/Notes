# @Autowired

无论是使用@Component注解还是其他注解，它们本质上都是将一个类实例化为Spring bean，并将其添加到Spring容器中管理。在应用程序中，可以使用@Autowired或@Resource等注解将这些bean注入到其他组件中，以便在应用程序中使用它们。

```java
public class UserService {
    private UserRepository repository;
    @Autowired
    public UserService(UserRepository repository) {
        this.repository = repository;
    }
}
-----------------------
public class UserService {
    private UserRepository repository;
    @Autowired
    public void setRepository(UserRepository repository) {
        this.repository = repository;
    }
}
-------------------------
public class UserService {
    @Autowired
    private UserRepository repository;
}
```

**其中构造注入：**
@Autowired并不是必须的，不加也能注入成功，这是为什么？

在 Spring4.x 中增加了新的特性：如果类只提供了一个带参数的构造方法，则不需要对对其内部的属性写 @Autowired 注解，Spring 会自动为你注入属性