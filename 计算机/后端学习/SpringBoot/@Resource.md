# @Resource

## 介绍
@Resource 是一个注解，用于将一个指定名称的 bean 注入到被注解的字段、属性或方法中。它是 JavaEE 规范中的注解，在 Spring 框架中也被支持。

与 @Autowired 不同的是，@Resource 注解没有 required 属性，并且可以通过 name 属性指定需要注入的 bean 的名称。如果没有指定名称，则默认使用与注解标记的字段、属性或方法同名的 bean。

```java
public class UserService {
    @Resource
    private UserDao userDao;

    public User getUserById(int id) {
        return userDao.getUserById(id);
    }
}
```
在这个例子中，@Resource 注解将名为 userDao 的 bean 注入到 userService 类的私有字段中。

## @Autowired 和 @Resource 的区别

### 查找顺序

* @Autowired 先根据类型（byType）查找，如果存在多个（Bean）再根据名称（byName）进行查找；
* @Resource 先根据名称（byName）查找，如果（根据名称）查找不到，再根据类型（byType）进行查找。

### 参数
* @Resource 注解设置 name 和 type 参数
* 但二者支持的参数以及参数的个数完全不同，其中 @Autowired 只支持设置一个 required 的参数，而 @Resource 支持 7 个参数

### 依赖注入的支持不同
依赖注入的用法支持不同：
* @Autowired 既支持**构造方法注入**，又支持属性注入和 Setter 注入，
* @Resource 只支持属性注入和 Setter 注入；

### 编译器 IDEA 的提示不同

当注入 Mapper 对象时，使用 @Autowired 注解编译器会提示错误，而使用 @Resource 注解则不会提示错误。

虽然 IDEA 会出现报错信息，但程序是可以正常执行的。