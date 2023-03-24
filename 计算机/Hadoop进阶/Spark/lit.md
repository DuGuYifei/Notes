# lit


lit()是PySpark中的一个函数，用于将常量值转换为DataFrame中的一个列。它可以将数字、字符串、布尔值等常量转换为与DataFrame中其他列相同类型的列，从而方便进行列之间的操作。

例如，在PySpark中可以使用lit()函数来创建一个新列，该列的值全部为常量1，示例如下：
```python
from pyspark.sql.functions import lit

df = spark.createDataFrame([(1, 'A'), (2, 'B'), (3, 'C')], ['id', 'name'])
df = df.withColumn('new_column', lit(1))
df.show()

+---+----+----------+
| id|name|new_column|
+---+----+----------+
|  1|   A|         1|
|  2|   B|         1|
|  3|   C|         1|
+---+----+----------+
```
