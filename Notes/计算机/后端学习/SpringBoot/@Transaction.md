# @Transaction

老旧了不需要了

[Spring 之 @Transaction 详解_岁月安然的博客-CSDN博客_@transaction](https://blog.csdn.net/baidu_38083619/article/details/106085287)

@Transaction 是 Spring 提供用来控制事务回滚/提交的一个注解，让我们从编程式注解转换到声明式注解。在这里就不做过多的撰述，今天主要来看下 @Transaction 里面的属性使用。

@Transaction 可以写在类、接口、方法上

1. 当标注在类上的时候：表示给该类所有的 public 方法添加上 @Transaction 注解
2. 当标注在接口上的时候：Spring 建议不要在接口或者接口方法上使用该注解，因为这只有在使用基于接口的代理时它才会生效。像 CGLib 动态代理采用继承的方式将会导致 @Transactional 注解失效
3. 当标注在方法上的时候：事务的作用域就只在该方法上生效，并且如果类及方法上都配置 @Transaction 注解时，方法的注解会覆盖类上的注解

字段名 | 类型 | 含义
----|----|---
value | String | 主要用来指定不同的事务管理器满足在同一个系统中，存在不同的事务管理器
propagation | enum: Propagation | 可选的事务传播行为设置
isolation | enum: Isolation | 可选的事务隔离级别设置
readOnly | boolean | 读写或只读事务，默认读写
timeout | int (in seconds granularity) | 事务超时时间设置
rollbackFor | Class对象数组，必须继承自Throwable | 导致事务回滚的异常类数组
rollbackForClassName | 类名数组，必须继承自Throwable | 导致事务回滚的异常类名字数组
noRollbackFor | Class对象数组，必须继承自Throwable | 不会导致事务回滚的异常类数组
noRollbackForClassName | 类名数组，必须继承自Throwable | 不会导致事务回滚的异常类名字数组

## value
value 主要用来指定不同的事务管理器，满足在同一个系统中，存在不同的事务管理器。如果在 Spring 中，配置了多个数据源声明了多个事务管理器，可以通过该参数来进行指定事务管理器。

## propagation
事务传播行为有一下7种，默认是 REQUIRED 传播机制。

值 | 含义
--|---
REQUIRED | 如果当前存在事务，则加入该事务；如果当前不存在事务，则创建一个新的事务；
SUPPORTS | 如果当前存在事务，则加入该事务；如果当前不存在事务，则以非事务的方式继续运行；
MANDATORY | 如果当前存在事务，则加入该事务；如果当前不存在事务，则抛出异常；
REQUIRES_NEW | 如果当前不存在事务，重新创建一个新的事务；如果当前存在事务，则暂停当前的事务；
NOT_SUPPORTED | 以非事务的方式运行 如果当前存在事务，则暂停当前的事务
NEVER | 以非事务的方式运行 如果当前存在事务，则抛出异常
NESTED | 如果当前存在事务，则在该事务内嵌套事务运行；如果当前不存在事务，则创建一个新的事务；

## 手动回滚
spring 也提供了 @Transaction 对应的手动回滚方式

TransactionAspectSupport.currentTransactionStatus().setRollbackOnly();
如果在代码中一定要 catch 住异常记得使用手动回滚的方式或者重新抛出一个异常。

## 失效场景
接下来看一下场景的 @Transaction 注解失效的场景，希望大家以后能够避免踩坑：

@Transactional 应用在非 public 修饰的方法上
@Transactional 注解属性 propagation 设置问题
@Transactional 注解属性 rollbackFor、noRollbackFor 设置问题
同一个类中方法调用，导致 @Transactional 失效
异常被 catch 导致 @Transactional 失效