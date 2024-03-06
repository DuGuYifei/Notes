# Any类型
使用
--

```text-x-ruby
message Response {
  int32 status = 2;
  string message = 1;
  google.protobuf.Any data = 3;
}
```

java填入和提出数据
-----------

```text-x-ruby
Any any = Any.pack(customMessage);
if (any.is(MyCustomMessage.class)) {
    MyCustomMessage customMessage = any.unpack(MyCustomMessage.class);
    // 使用 customMessage
}
```