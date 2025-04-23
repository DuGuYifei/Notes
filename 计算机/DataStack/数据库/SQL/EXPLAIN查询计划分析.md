# EXPLAIN查询计划分析

## 什么是 `EXPLAIN`？

> **`EXPLAIN` 是 SQL 中用来查看某个查询的执行计划（Query Execution Plan）的语句。**

它会告诉你：**数据库“打算怎么执行”你写的 SQL 查询**，比如：
- 它会不会用索引？
- 它会先 JOIN 哪个表？
- 扫描了多少行数据？
- 哪一步最耗时？

---

## 常见数据库中的使用方式：

```sql
-- PostgreSQL / MySQL / SQLite
EXPLAIN SELECT * FROM orders WHERE customer_id = 123;

-- PostgreSQL + 显示估算行数、耗时
EXPLAIN ANALYZE SELECT * FROM orders WHERE customer_id = 123;
```

---

## 输出长什么样？（PostgreSQL 示例）

```text
Seq Scan on orders  (cost=0.00..431.00 rows=50 width=4)
  Filter: (customer_id = 123)
```

这说明：
- 这是一个 **顺序扫描（Seq Scan）**，没用索引 → 慢
- 估计会处理 431 行
- 最终返回 50 行

---

## 优化场景示例：

```sql
-- 查询执行前加 EXPLAIN 看一下
EXPLAIN SELECT * FROM orders WHERE order_date = '2023-01-01';
```

如果结果是：

```text
Index Scan using idx_order_date on orders ...
```

就说明数据库成功使用了你建的索引（`idx_order_date`） → 查询很快 ✅

但如果是：

```text
Seq Scan on orders ...
```

说明全表扫描了 → 可能慢，需要加索引或改写逻辑 ❌

---

## 常用关键词解释（MySQL / PostgreSQL 通用）

| 字段/术语           | 意义                                  |
|----------------------|-----------------------------------------|
| `Seq Scan` / `Full Table Scan` | 全表扫描，最慢                        |
| `Index Scan` / `Index Range`  | 用到了索引，较快                      |
| `Rows` / `rows`       | 预计处理的行数                          |
| `Join Type`（Nested Loop / Hash） | JOIN 策略                          |
| `Cost`（Postgres）    | 执行成本估算，用于判断查询代价           |
| `Filter`              | WHERE 条件，是否提前下推（谓词下推）     |

---

## 总结一张嘴能讲清：

`EXPLAIN` 让你看懂数据库是怎么跑你的 SQL 的，是性能优化的第一步。 

你可以用它确认是否用了索引，是否 JOIN 顺序合理，是否存在全表扫描，从而优化查询效率。