# GraphQL

GraphQL 是 Facebook 于 2012 年开源的一种数据查询语言，它的目标是提供一种更加简洁的数据查询方式。GraphQL 与 RESTful API 的最大区别在于，GraphQL 只提供一个查询接口，而不是提供多个接口。GraphQL 的查询接口是一个 URL，客户端向这个 URL 发送一个请求，请求的内容是一个查询语句，服务器接收到请求后，执行查询语句并返回查询结果。GraphQL 的查询语句是一个 JSON 对象，它的结构如下：
```json
{
  "query": "query { ... }",
  "variables": { "myVariable": "someValue", ... },
  "operationName": "myOperation"
}
```