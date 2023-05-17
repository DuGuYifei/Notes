# @Configuration

## 作用

1. 用于定义配置类，可替换xml配置文件
2. 被注解的类内部包含有一个或多个被`@Bean`注解的方法，这些方法将会被`AnnotationConfigApplicationContext`或`AnnotationConfigWebApplicationContext`类进行扫描，并用于构建bean定义，初始化Spring容器。

## 本质

`@Configuration`是组合注解，组合了`@Component`注解，所以配置类本质上也是一个`@Component`，Spring容器会自动发现并加载它们。

与[@Bean](%40Bean%E5%92%8C%40Component%E5%8C%BA%E5%88%AB.md)结合。Bean注解的方法名就是Bean的id，返回值就是Bean的类型，返回值就是Bean的实例。