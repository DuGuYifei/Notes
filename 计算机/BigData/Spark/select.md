# select

SQL 的 SELECT 的 Spark 变体是 .select() 方法。 此方法采用多个参数 - 一个用于您要选择的每一列。 这些参数可以是作为字符串的列名称（每列一个）或列对象（使用 df.colName 语法）。 当你传递一个列对象时，你可以对列执行加法或减法等操作来更改其中包含的数据，就像在 .withColumn() 中一样。

```python
# Select the first set of columns
selected1 = flights.select("tailnum", "origin", "dest")

# Select the second set of columns
temp = flights.select(flights.origin, flights.dest, flights.carrier)

# Define first filter
filterA = flights.origin == "SEA"

# Define second filter
filterB = flights.dest == "PDX"

# Filter the data, first by filterA then by filterB
selected2 = temp.filter(filterA).filter(filterB)
```