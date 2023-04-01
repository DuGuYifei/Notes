# reduceByKey

reduceByKey是Spark中用于对键值对RDD进行聚合操作的一种函数。该函数对具有相同键的所有值进行聚合，并返回一个新的键值对RDD，其中键是唯一的，值是应用于相同键的聚合函数的结果。通常用于在MapReduce任务中进行reduce操作，以在并行处理的情况下有效地减少数据量。

```python
# Create PairRDD Rdd with key value pairs
Rdd = sc.parallelize([(1,2),(3,4),(3,6),(4,5)])

# Apply reduceByKey() operation on Rdd
Rdd_Reduced = Rdd.reduceByKey(lambda x, y: x + y)

# Iterate over the result and print the output
for num in Rdd_Reduced.collect(): 
  print("Key {} has {} Counts".format(num[0], num[1]))
```