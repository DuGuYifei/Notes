# @Bean和@Component区别

[@bean注解和@component注解的区别_Spring 中的一些注解_我鸿的博客-CSDN博客](https://blog.csdn.net/weixin_35544490/article/details/112143211)

1. 作用对象不同：@Component 注解作用于**类**，而 @Bean 注解作用于**方法**
2. @Component 通常是通过路径扫描来**自动侦测以及自动装配到 Spring 容器中**(我们可以使用 @ComponentScan 注解定义要扫描的路径从中找出标识了需要装配的类自动装配到 Spring 的 bean 容器中)。@Bean 注解通常是我们在标有该注解的方法中定义产生这个 bean，**@Bean 告诉了 Spring 这是某个类的实例，当我们需要用它的时候还给我。**
3. @Bean 注解比 @Component 注解的**自定义性更强**，而且很多地方我们只能通过 @Bean 注解来注册 bean。比如当我们引用第三方库中的类需要装配到 Spring 容器时，只能通过 @Bean 来实现。

**为什么有了@Compent,还需要@Bean呢？**
* 如果想将第三方的类变成组件，你又没有没有源代码，也就没办法使用@Component进行自动配置，这种时候使用@Bean就比较合适了。不过同样的也可以通过xml方式来定义。
* 另外@Bean注解的方法**返回值是对象**，可以在方法中为对象设置属性。

```java
@Configuration
public class AppConfig {    
    @Bean
    public TransferService transferService() {return new TransferServiceImpl();    }
}

@Component
public class ServiceImpl implements AService {    ....}
```

下面这个例子是通过 @Component 无法实现的：
```java
@Bean
public OneService getService(status) {
    case (status)  {
        when 1:return new serviceImpl1();
        when 2:return new serviceImpl2();
        when 3:return new serviceImpl3();    
    }
}
```
