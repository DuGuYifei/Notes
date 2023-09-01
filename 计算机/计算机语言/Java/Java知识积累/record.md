# record

## 简介
record 是 Java 14 中引入的一种新的引用类型，它是一种透明的、不可变的数据持有类，它的目的是用来替代那些只包含数据的类。record 类似于 C# 中的 record，Kotlin 中的 data class，Scala 中的 case class。

## 特殊问题

1. 是Object吗？
    - 不是，record是一个类，它继承自java.lang.Record，而不是java.lang.Object。
2. 那么如果在ResponseEntity传输时，可以默认json吗？ （待验证）
    - 可以，但是需要在pom.xml中引入jackson-databind依赖，否则会报错。