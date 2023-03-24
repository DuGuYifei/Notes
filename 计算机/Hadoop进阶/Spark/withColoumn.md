# withColoumn

withColumn()方法可以用于替换DataFrame中的列或创建新的列，返回一个新的DataFrame。

```python
df_after = df_before.withColumn('in', rm_trivial_udf('in'))\
                    .withColumn('out', rm_trivial_udf('out'))
```