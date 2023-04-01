# registerTempTable

在 Spark 2.0 及以后的版本中，registerTempTable 已经被废弃了，取而代之的是 createOrReplaceTempView 方法。

registerTempTable()是Spark中用于将DataFrame注册为一个临时表（temporary table）的方法。它将DataFrame注册为一个SQL可查询的表，因此可以使用SQL查询语句对其进行查询。

```PYTHON
df = spark.read.format("csv").load("path/to/data.csv", header=True, inferSchema=True)
df.registerTempTable("my_table")

# SQL query against temporary table
result = spark.sql("SELECT * FROM my_table WHERE age >= 18")
```