# HAVING

`HAVING` is used to filter the result of `GROUP BY` clause.

```sql
SELECT column_name, aggregate_function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name
HAVING aggregate_function(column_name) operator value;
```

## Example

```sql
SELECT name, COUNT(*) as cnt
FROM student
GROUP BY name
HAVING cnt > 1;
```
意思是：统计student表中，每个name出现的次数，然后筛选出出现次数大于1的name。

```sql
SELECT SUM(amount) AS balance
FROM (
  SELECT 
    CASE
      -- 充值金额
      WHEN amount > 0 THEN amount
      -- 购物金额
      WHEN amount < 0 THEN 
        CASE
          -- 购物金额大于等于50元，不收取停车费
          WHEN -amount >= 50 THEN amount
          -- 购物金额小于50元，收取5元停车费
          ELSE amount - 5
        END
      -- 0元记录和停车费不计入余额
      ELSE 0
    END AS amount
  FROM transaction
  WHERE 
    -- 只考虑2022年的记录
    date >= '2022-01-01' AND date <= '2022-12-31'
    -- 停车费不计入余额
    AND amount > -5
) t
-- 如果月度购物总额大于等于1000元或购物次数大于等于5次，本月停车费豁免
GROUP BY YEAR(date), MONTH(date)
HAVING 
  SUM(CASE WHEN amount < 0 THEN -amount ELSE 0 END) >= 1000
  OR COUNT(CASE WHEN amount < 0 THEN 1 END) >= 5
```