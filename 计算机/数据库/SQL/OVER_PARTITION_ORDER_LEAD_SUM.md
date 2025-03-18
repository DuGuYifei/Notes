# LEAD_OVER_PARTITION_ORDER

```sql
SELECT salesperson, sales_month, sales_amount,
       LEAD(sales_amount) OVER (PARTITION BY salesperson ORDER BY sales_month) AS next_month_sales
FROM sales

SELECT train_id, station, time, diff_min,
SUM(diff_min) OVER (PARTITION BY train_id ORDER BY time) AS running_total
FROM schedule
```

SUM可以使下一行对前一行的值进行累加

LEAD 函数用于获取当前行之后的某一行的值。例如，假设有一个名为 sales 的表，其中包含每个销售员每月的销售额。您可以使用 LEAD 函数来获取每个销售员下个月的销售额

lead函数的第二个参数是一个整数，用于指定要获取的后续行数，默认值为1。

上述代码中，LEAD(sales_amount) OVER (PARTITION BY salesperson ORDER BY sales_month) 表示获取每个销售员下个月的销售额，PARTITION BY 表示按照销售员进行分区，ORDER BY 表示按照销售月份进行排序。

OVER 关键字用于指定窗口函数的分区和排序方式。在上述例子中，我们使用了 PARTITION BY 和 ORDER BY 子句来分区和排序。

通过使用窗口函数，您可以在不影响结果集的情况下对结果进行排序、聚合、计算等操作，从而使 SQL 语句更加灵活和强大。