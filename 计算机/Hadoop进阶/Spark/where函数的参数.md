# where函数的参数

是的，where()函数在PySpark中可以支持多种表达式作为输入参数，包括字符串表达式和列表达式。当输入参数是字符串表达式时，它会根据字符串表达式的逻辑条件来筛选数据集中的记录，只返回符合条件的记录。

```python
>>> df.where("age > 21").show()
+----+-------+
| age|   name|
+----+-------+
|  30|Michael|
|  19| Justin|
+----+-------+

df_true = df.where("endword in ('she','he','hers','his','her',him')").withColumn('label',lit(1)) 
```

