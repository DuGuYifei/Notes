# @Transactional


## @Transactional和@Transaction的区别
`@Transactional`注解是Spring框架中用于管理事务的注解，用于标记一个方法或类需要在事务管理下运行。它可以配置一些属性，例如事务的隔离级别、传播行为、超时时间等。同时，它也可以让测试方法在独立的事务中执行，并可以自动回滚事务。

`@Transaction`注解是Spring早期版本中提供的一个事务管理注解，用于标记一个方法或类需要在事务管理下运行，通常需要与TransactionManager等其他组件一起使用来实现事务控制。

由于@Transactional注解提供了更加灵活和方便的事务管理方式，所以在Spring框架中，@Transaction注解已经不再被推荐使用，推荐使用@Transactional注解来管理事务。

## 作用
可以成功自动提交，失败自动回滚

## 案例
```java
@Service
public class UserServiceImpl implements UserService {
	@Autowired
	private UserDao userDao;

	@Override
	@Transactional
	public void save(User user) {
		userDao.save(user);
		int i = 1 / 0;
	}
}
```

## 和@Rollback配合
[@Rollback](@Rollback.md)