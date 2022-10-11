# 数据库其他知识积累

## ACID

[谈谈数据库的ACID - 随心勿欲 - 博客园](https://www.cnblogs.com/lichunyang321/p/9594196.html)

1. Atomicity
2. Consistency
3. Isolation
   1. 事务之间的相互影响
      - dirty read
      - 不可重复读
      - 幻读
      - lost update
   2. 隔离层级
      - Read Uncommitted
      - read Committed (解决 Dirty Read 和 Lost Update)
      - Reapeatable Read
      - Serializable
4. Durability

