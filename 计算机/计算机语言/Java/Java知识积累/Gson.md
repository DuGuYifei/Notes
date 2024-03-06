# Gson

## 1. Gson简介

Gson是Google提供的用来在Java对象和JSON数据之间进行映射的Java类库。可以将一个Json字符转换成一个Java对象，或者将一个Java转换成Json字符串。

## 2. Gson的使用

```java
// 1. 创建Gson对象
Gson gson = new Gson();

// 2. 将Java对象转换成Json字符串
String json = gson.toJson(obj);
```
## 3. 去除某个字段

https://www.baeldung.com/gson-exclude-fields-serialization

1. [transient](transient%E5%92%8C%E5%BA%8F%E5%88%97%E5%8C%96(Serialization).md), 但是注意使用它同时会无法保存到数据库，因为彻底无法序列化
2. `@Expose`注解，需要序列化的加上就行，然后`Gson gson = new GsonBuilder().excludeFieldsWithoutExposeAnnotation().create();`
3. `Strategy`，自定义一个类。

详见上面链接。
