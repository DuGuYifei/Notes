# @service_@repository和@component的本质区别

@component是通用性的注解，

@service 和@repository则是在@component的基础上添加了特定的功能。

所以@component可以替换为@service和@repository，

但是为了规范，服务层bean用@service，dao层用@repository。
就好比代码规范，变量、方法命名一样。还有一点，正如文档描述那样：
```
@Repository的工作是捕获特定于平台的异常，并将它们作为Spring统一未检查异常的一部分重新抛出。为此，提供了PersistenceExceptionTranslationPostProcessor。
```
如果在dao层使用@service，就不能达到这样的目的。