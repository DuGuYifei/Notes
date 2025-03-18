# @ConditionalOnProfile

## 1. 作用

`@ConditionalOnProfile`注解可以让我们在不同的环境中，配置不同的Bean。

## 2. 代码

### profile是哪个
```java
@Component
@ConditionalOnProfile({"dev", "qa"})
public class MyComponent {
    // ...
}
```
在上面的示例中，@ConditionalOnProfile注解的参数是一个String类型的数组，其中包含了要检查的profile名称。如果当前环境中激活的profile包含了数组中的任意一个名称，则MyComponent组件会被实例化。

### profile包含什么值
```java
@Component
@ConditionalOnProfile(name = "db.type", havingValue = "mysql")
public class MyComponent {
    // ...
}
```
在上面的示例中，@ConditionalOnProfile注解的name参数指定了要检查的属性名称为db.type，havingValue参数指定了对应的属性值为mysql。如果当前环境中激活的profile包含了这个属性，并且其值为mysql，则MyComponent组件会被实例化。