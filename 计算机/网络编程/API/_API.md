# API

## RESTful

[RESTful](RESTful/_RESTful.md)

传统的 RESTful API 以资源为中心，通过 HTTP 方法（如 GET、POST、PUT、DELETE 等）对资源进行操作，返回 JSON 或 XML 格式的数据。

## GraphQL

[GraphQL](GraphQL/_GraphQL.md)

GraphQL 是一种用于构建 API 的查询语言和运行时。它由 Facebook 开发，旨在提高客户端和服务器之间数据交互的效率和灵活性。GraphQL 允许客户端精确指定所需的数据和数据结构，从而避免了传统 RESTful API 的一些缺点，例如过多或过少的数据、多个请求导致的数据重复和混乱的嵌套结构。

## gRPC

gRPC 是一种高性能的远程过程调用（RPC）框架，使用 Protocol Buffers 作为数据序列化格式。与 GraphQL 相比，gRPC 可以在多种语言和平台上使用，支持多种协议和负载类型，提供了更高效的序列化和反序列化能力。

## Falcor

Falcor 是 Netflix 开源的一种前端数据获取框架，它采用类似于 GraphQL 的数据获取方式，支持对数据进行精确查询，并提供了自动缓存和数据预取等功能。

## OData

OData（Open Data Protocol）是一种面向数据的 Web API 协议，支持通过 RESTful API 或 SOAP API 访问数据，提供了统一的查询语言和元数据描述。