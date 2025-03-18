# Bucketizer

在特征工程中，一种常见的方法是使用特征桶化。特征桶化将连续变量划分为离散的区间，为每个区间分配一个标签，从而将连续变量转换为离散的分类变量。这样的离散变量通常比原始的连续变量更具预测能力。

在特征桶化过程中，首先确定桶或区间的边界，然后创建一个桶化器对象，并指定输入和输出列的名称以及边界。通过调用transform()方法将桶化器应用于数据，生成一个新的列，其中包含离散的桶值。

在一些情况下，需要对桶化后的离散变量进行独热编码，以便在回归模型中使用。独热编码将离散变量映射为多个虚拟变量，其中某个桶被作为参考级别，不会得到单独的虚拟变量。

除了桶化，特征工程还包括其他方法，如通过对一个或多个列应用算术操作来创建新特征。例如，可以通过将质量和身高数据结合计算BMI指数，从而得到比单独的身高或质量更具预测能力的特征。

特征工程是发现强大新特征的过程，常常需要尝试和实验。在建模过程中，通过试错来发现仅有意义的预测变量。在回归模型中，选择相关的预测变量是一个重要的技术，将在下一课程中介绍。

在处理航班数据时，可以应用特征工程的概念，对数据进行处理和转换，以提取更有用的特征。

```python
from pyspark.ml.feature import Bucketizer, OneHotEncoder

# Create buckets at 3 hour intervals through the day
buckets = Bucketizer(splits=[0, 3, 6, 9, 12, 15, 18, 21, 24], inputCol='depart', outputCol='depart_bucket')

# Bucket the departure times
bucketed = buckets.transform(flights)
bucketed.select('depart', 'depart_bucket').show(5)

# Create a one-hot encoder
onehot = OneHotEncoder(inputCols=['depart_bucket'], outputCols=['depart_dummy'])

# One-hot encode the bucketed departure times
flights_onehot = onehot.fit(bucketed).transform(bucketed)
flights_onehot.select('depart', 'depart_bucket', 'depart_dummy').show(5)
```