# take

相当于pandas的head

```python
# Filter the fileRDD to select lines with Spark keyword
fileRDD_filter = fileRDD.filter(lambda line: 'Spark' in line)

# How many lines are there in fileRDD?
print("The total number of lines with the keyword Spark is", fileRDD_filter.count())

# Print the first four lines of fileRDD
for line in fileRDD_filter.take(4): 
  print(line)
```

## 和show
take() 是针对 RDD 的操作，show() 是针对 DataFrame 的操作，

take()方法可以用于DataFrame。

这两个操作可以方便地查看数据的前几行，但是需要注意的是，
1. take 是在 Driver 端执行的操作，因此当数据量较大时可能会引起性能问题，
2. 而 show 是在 Executor 端执行的操作，因此在**分布式集群上处理大规模数据时更为高效**。