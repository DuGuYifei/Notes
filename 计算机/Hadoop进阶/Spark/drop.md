# drop


```python
df.withColumn('label',k_udf('outvec')).drop('outvec')
```
drop函数删除了一个名为"outvec'"的列