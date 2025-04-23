# corr()

corr() 是 PySpark DataFrame 的一个方法，用于计算两列之间的相关性（correlation）。它可以用来确定两列之间的线性关系强度。corr() 方法返回一个浮点数，表示两列之间的相关性，取值范围在 -1 到 1 之间。

具体用法如下：

```python
correlation = df.corr(column1, column2)
```