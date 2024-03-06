# Transformers and Estimators

## 1. Transformers
Transformer 类有一个 .transform() 方法，它**接受一个 DataFrame 并返回一个新的 DataFrame**； 通常是原始的附加了一个新列。 

例如，您可以使用 Bucketizer 类从连续特征创建离散 bin，或使用 PCA 类使用主成分分析来降低数据集的维数。

## 2. Estimators
Estimator 类都实现了 .fit() 方法。这些方法也**接受一个 DataFrame**，但是不像 Transformer，它们**返回一个模型对象**，其实就是Transformer。

例如用于在模型中包含字符串格式的分类数据的 StringIndexerModel，或者使用随机森林算法进行分类或回归的 RandomForestModel。