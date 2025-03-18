# HashingTF

HashingTF是PySpark的一个机器学习库中用于特征提取的类，其全称是Hashing Term Frequency。它可以将一组文档转换为一组向量，其中每个文档都被表示为一个向量，向量的长度为指定的哈希表大小。每个单词都映射到该哈希表中的一个索引位置，并用单词的出现次数填充相应的向量位置。由于哈希函数的使用，HashingTF不需要维护一个全局字典来存储单词和索引之间的映射，因此它适用于处理大规模文本数据集。

`tf = HashingTF(numFeatures=200)`

```python
# Create a HashingTf instance with 200 features
tf = HashingTF(numFeatures=200)

# Map each word to one feature
spam_features = tf.transform(spam_words)
non_spam_features = tf.transform(non_spam_words)

# Label the features: 1 for spam, 0 for non-spam
spam_samples = spam_features.map(lambda features:LabeledPoint(1, features))
non_spam_samples = non_spam_features.map(lambda features:LabeledPoint(0, features))

# Combine the two datasets
samples = spam_samples.union(non_spam_samples)
```