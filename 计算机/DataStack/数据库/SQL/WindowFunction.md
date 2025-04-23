# Window Function

Window Function 是一种 SQL 函数，它允许对查询结果的某个窗口（Window）进行计算。窗口可以被定义为数据集中的一部分，这个数据集可能是整个表，也可能是由 GROUP BY 或 PARTITION BY 子句分组后的一个子集。Window Function 可以对窗口中的每一行计算一个单独的值，并将该值作为新列添加到结果集中。Window Function 可以用来计算排名、累计和、移动平均值等统计量。Window Function 在处理时间序列数据和分析数据中经常用到。Window Function 的语法和具体用法可能会因所使用的数据库软件而有所不同。

窗口函数类似于聚合函数，不同之处在于它为数据集中的每一行提供输出，而不是每组输出一行。

您可以与窗口函数一起进行聚合。 使用窗口函数的运行总和比使用`join`所需的更简单。 查询持续时间也可以快得多。

为您提供了一个名为 schedule 的表，其中包含 train_id、station、time 和 diff_min 列。 diff_min 列给出了当前站和线路上下一站之间经过的时间。

```sql
函数名() OVER (
  PARTITION BY 分组字段
  ORDER BY 排序字段
)
```

1. 排名类：`ROW_NUMBER(), RANK(), DENSE_RANK()`
2. 时序类：`LAG(), LEAD()`
3. 聚合类：`SUM() OVER(PARTITION BY ...)`

## ROW_NUMBER

返回每一行的行号

```sql
SELECT
  customer_id,
  order_date,
  amount,
  ROW_NUMBER() OVER (
    PARTITION BY customer_id
    ORDER BY order_date
  ) AS order_rank
FROM orders;
```

## RANK
```sql
SELECT
  customer_id,
  order_date,
  amount,
  RANK() OVER (
    PARTITION BY customer_id
    ORDER BY order_date
  ) AS order_rank
FROM orders;
```

RANK 函数用于为每一行分配一个唯一的排名值。 如果有两个或多个行具有相同的值，则它们将获得相同的排名值。 但是，排名值之间会有间隔。例如，如果有两个行具有相同的排名值 1，则下一个行将获得排名值 3，而不是 2。

## DENSE_RANK
```sql
SELECT
  customer_id,
  order_date,
  amount,
  DENSE_RANK() OVER (
    PARTITION BY customer_id
    ORDER BY order_date
  ) AS order_rank
FROM orders;
```

DENSE_RANK 函数与 RANK 函数类似，但它不会在排名值之间留下间隔。 如果有两个行具有相同的排名值 1，则下一个行将获得排名值 2，而不是 3。

## LAG

```sql
SELECT salesperson, sales_month, sales_amount,
       LAG(sales_amount) OVER (PARTITION BY salesperson ORDER BY sales_month) AS last_month_sales
FROM sales
```

LAG 函数用于获取当前行之前的某一行的值。例如，假设有一个名为 sales 的表，其中包含每个销售员每月的销售额。您可以使用 LAG 函数来获取每个销售员上个月的销售额。

lag函数的第二个参数是一个整数，用于指定要获取的前一行数，默认值为1。即LAG(sales_amount, 1) 等同于 LAG(sales_amount)。

## LEAD

```sql
SELECT salesperson, sales_month, sales_amount,
       LEAD(sales_amount) OVER (PARTITION BY salesperson ORDER BY sales_month) AS next_month_sales
FROM sales
```

LEAD 函数用于获取当前行之后的某一行的值。例如，假设有一个名为 sales 的表，其中包含每个销售员每月的销售额。您可以使用 LEAD 函数来获取每个销售员下个月的销售额

lead函数的第二个参数是一个整数，用于指定要获取的后续行数，默认值为1。即LEAD(sales_amount, 1) 等同于 LEAD(sales_amount)。

上述代码中，LEAD(sales_amount) OVER (PARTITION BY salesperson ORDER BY sales_month) 表示获取每个销售员下个月的销售额，PARTITION BY 表示按照销售员进行分区，ORDER BY 表示按照销售月份进行排序。

OVER 关键字用于指定窗口函数的分区和排序方式。在上述例子中，我们使用了 PARTITION BY 和 ORDER BY 子句来分区和排序。

## SUM
```sql
SELECT train_id, station, time, diff_min,
SUM(diff_min) OVER (PARTITION BY train_id ORDER BY time) AS running_total
FROM schedule
```

SUM可以使下一行对前一行的值进行累加
