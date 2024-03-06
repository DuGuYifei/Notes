# groupBy和agg

## groupBy
```python
# Find the shortest flight from PDX in terms of distance
flights.filter(flights.origin == "PDX").groupBy().min("distance").show()

# Find the longest flight from SEA in terms of air time
flights.filter(flights.origin == "SEA").groupBy().max("air_time").show()
```

groupBy()不传递参数相当于对整个DataFrame进行groupBy，这样就可以使用聚合函数了。但是不能省略gorupBy()，否则会报错。

## 如果有多个聚合函数，可以使用agg
```python
# 同时多个聚合函数
from pyspark.sql.functions import avg, max, min

flights.groupBy("origin").agg(avg("dep_delay"), max("dep_delay"), min("dep_delay"))
```

## 其他聚合函数

### count
```python
# Count the number of flights
flights.count()
```

### stddev
参数是列名，返回的是标准差。

参数只能用字符串的列名，不能用列对象。

```python
# Import pyspark.sql.functions as F
import pyspark.sql.functions as F

# Group by month and dest
by_month_dest = flights.groupBy("month", "dest")

# Average departure delay by month and destination
by_month_dest.avg("dep_delay").show()

# Standard deviation of departure delay
by_month_dest.agg(F.stddev("dep_delay")).show()
```

### union
```python
df_examples = df_true.union(df_false)
```