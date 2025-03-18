# MyBatis

## 简介

MyBatis一开始为了方便只是为了可以轻松在xml里写select语句，然而现在mapper可以直接写sql注解，然后也是为了不像spring data jpa 那样难以学习，所以才用MyBatis。现在直接使用Spring data jpa就好了，反正也不难，而且也可以直接@Query注解之类的。

## mapper案例
    
```java
@Mapper
public interface UserMapper {
    @Select("select * from user where id = #{id}")
    User getUserById(@Param("id") int id);
}
```

```java
public interface UserService {
    User getUserById(int id);
}
```

使用mapper interface
```java
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;

    public User getUserById(int id) {
        return userMapper.getUserById(id);
    }
}
```
