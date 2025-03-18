# @Rollback

@Rollback(true)是Spring Test框架中的注解之一，用于测试方法的事务管理。

当我们使用JUnit或其他测试框架来编写单元测试时，经常需要对数据库进行读写操作，为了避免对测试环境产生影响，我们通常会使用事务管理来确保每个测试方法都在独立的事务中执行。

在Spring Test框架中，使用@Rollback注解可以设置测试方法执行后是否回滚事务。当@Rollback注解的参数为true时，测试方法执行后会回滚事务，撤销对数据库的修改；当参数为false时，测试方法执行后不会回滚事务，对数据库的修改会被提交。

```java
@RunWith(SpringRunner.class)
@SpringBootTest
@Transactional
public class UserServiceTest {

    @Autowired
    private UserService userService;

    @Test
    @Rollback(true)
    public void testAddUser() {
        User user = new User();
        user.setName("Tom");
        user.setAge(20);
        userService.addUser(user);
        // ...
    }

    // ...
}
```