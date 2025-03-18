# Window Function

Window Function 是一种 SQL 函数，它允许对查询结果的某个窗口（Window）进行计算。窗口可以被定义为数据集中的一部分，这个数据集可能是整个表，也可能是由 GROUP BY 或 PARTITION BY 子句分组后的一个子集。Window Function 可以对窗口中的每一行计算一个单独的值，并将该值作为新列添加到结果集中。Window Function 可以用来计算排名、累计和、移动平均值等统计量。Window Function 在处理时间序列数据和分析数据中经常用到。Window Function 的语法和具体用法可能会因所使用的数据库软件而有所不同。

窗口函数类似于聚合函数，不同之处在于它为数据集中的每一行提供输出，而不是每组输出一行。

您可以与窗口函数一起进行聚合。 使用窗口函数的运行总和比使用`join`所需的更简单。 查询持续时间也可以快得多。

为您提供了一个名为 schedule 的表，其中包含 train_id、station、time 和 diff_min 列。 diff_min 列给出了当前站和线路上下一站之间经过的时间。

1. [OVER_PARTITION_ORDER_LEAD_SUM](OVER_PARTITION_ORDER_LEAD_SUM.md)
2. [ROW_NUMBER](ROW_NUMBER.md)
