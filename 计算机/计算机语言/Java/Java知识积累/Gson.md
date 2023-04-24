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

