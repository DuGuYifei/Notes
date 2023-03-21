# pyspark

1. [读取数据](#读取数据)
2. [创建表和查询](#创建表和查询)
3. [检查表结构](#检查表结构)
4. [窗口函数](#窗口函数)
	1. [WindowSpec](#windowspec)
5. [dot notation (col, alias, withColumnRenamed, withColumn, agg, orderBy, limit, lead, groupBy)](#dot-notation-col-alias-withcolumnrenamed-withcolumn-agg-orderby-limit-lead-groupby)
6. [groupBy](#groupby)
7. [Loading text](#loading-text)
	1. [parquet](#parquet)
	2. [truncate](#truncate)


## 读取数据

```python
from pyspark.sql import SparkSession
spark = SparkSession.builder.appName('appName').getOrCreate()
df = spark.read.csv('data.csv', header=True, inferSchema=True) 
# 读取txt也是一样的，默认是按照逗号分隔的

df = spark.read.csv(filename)
df = spark.read.csv(filename, header=True)
```

## 创建表和查询

```python
df.createOrReplaceTempView('table_name')
df = spark.sql('select * from table_name')
	.show()
```

## 检查表结构

```python
result = spark.sql('describe table_name')
result = spark.sql('SHOW COLUMNS FROM table_name')
result = spark.sql('select * from table_name limit 0')
result.show()
print(result.columns)
```

## 窗口函数
[WindowFunction](../../%E6%95%B0%E6%8D%AE%E5%BA%93/SQL/WindowFunction.md)

### WindowSpec
在Spark中，WindowSpec是用于定义窗口函数（Window Function）的类。窗口函数是一种特殊类型的聚合函数，它在分组数据上执行，但不会将结果缩减为单个行。相反，它将聚合计算应用于定义的窗口中的每一行，并返回结果作为新的列。

WindowSpec定义了窗口函数要应用的窗口范围，它包括以下组成部分：

1. 分区（Partition）：指定要分组计算的列，所有具有相同分区键值的行将被分组在一起。
2. 排序（Ordering）：指定窗口函数的排序方式，可以按照一个或多个列进行排序
3. 窗口范围（Window Frame）：指定要在分组数据上计算的行的范围。

```python
window = Window.partitionBy('train_id').orderBy('time')
dfx = df.withColumn('id', lead('time', 1).over(window))

type(window) # pyspark.sql.window.WindowSpec
```

## dot notation (col, alias, withColumnRenamed, withColumn, agg, orderBy, limit, lead, groupBy)

```python
from pyspark.sql.functions import col
df.select('train_id', 'station')
df.select(df.train_id, df.station)
df.select(col('train_id'), col('station'))

df.select('train_id', 'station').withColumnRenamed('train_id', 'train').show(5)
df.select(col('train_id').alias('train'), 'station').limit(5).show()
spark.sql('SELECT train_id AS train, station FROM schedule LIMIT 5').show()
```

```python
query = """
SELECT * ，
ROW_NUMBER() OVER (PARTITION BY train_id ORDER BY time) AS id
FROM schedule
"""
spark.sql(query).show(11)


from spark.sql import Window
from spark.sql.functions import row_number
df.withColumn("id", row_number().over(
			Window.partitionBy("train_id").orderBy("time")
		)
	)
```

## groupBy

```python
# Give the identical result in each command
spark.sql('SELECT train_id, MIN(time) AS start FROM schedule GROUP BY train_id').show()
df.groupBy('train_id').agg({'time':'min'}).withColumnRenamed('min(time)', 'start').show()

# Print the second column of the result
spark.sql('SELECT train_id, MIN(time), MAX(time) FROM schedule GROUP BY train_id').show()
result = df.groupBy('train_id').agg({'time':'min', 'time':'max'})
result.show()
print(result.columns[1])
```

## Loading text

```python
df = spark.read.text('data.txt')
print(df.first())
print(df.first().value)
print(df.count())
```

### parquet

```python
df = spark.read.load('data.parquet')
df.show(15, truncate=False)
```

### truncate
当truncate参数的值为True时（默认情况下），如果某一列的字符串长度超过了指定的宽度，PySpark将截断该字符串，并在结尾处添加省略号(...)以表示截断。当truncate参数的值为False时，则不对字符串进行截断，而是将完整的字符串显示出来。

