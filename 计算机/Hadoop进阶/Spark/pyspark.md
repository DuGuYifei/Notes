# pyspark

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

