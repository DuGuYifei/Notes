# CTE_WITH

Common Table Expression (CTE) 是一种 SQL 语法，用于在查询中定义临时结果集。CTE 可以使查询更易读，并且可以在同一查询中多次引用。CTE 通常用于递归查询、分层查询或复杂的联接操作。

`CTE` 的基本语法如下：

```sql
WITH max_orders AS (
  SELECT customer_id, MAX(amount) AS max_amount
  FROM orders
  GROUP BY customer_id
)
SELECT *
FROM max_orders
WHERE max_amount > 200;
```