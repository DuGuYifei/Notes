# Classification

## 数据
```python
# Load the datasets into RDDs
spam_rdd = sc.textFile(file_path_spam)
non_spam_rdd = sc.textFile(file_path_non_spam)

# Split the email messages into words
spam_words = spam_rdd.flatMap(lambda email: email.split(' '))
non_spam_words = non_spam_rdd.flatMap(lambda email: email.split(' '))

# Print the first element in the split RDD
print("The first element in spam_words is", spam_words.first())
print("The first element in non_spam_words is", non_spam_words.first())
```

## HasingTF
[HashingTF](HashingTF.md)

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

### LabeledPoint
LabeledPoint 是 PySpark MLlib 中用于分类或回归任务的数据类型，它表示一个带有标签的数据点，即一个向量和一个标签值。标签是数据点的已知结果或类别，而向量是一组相关特征的值。

## training 
```python
# Split the data into training and testing
train_samples,test_samples = samples.randomSplit([0.8, 0.2])

# Train the model
model = LogisticRegressionWithLBFGS.train(train_samples)

# Create a prediction label from the test data
predictions = model.predict(test_samples.map(lambda x: x.features))

# Combine original labels with the predicted labels
labels_and_preds = test_samples.map(lambda x: x.label).zip(predictions)

# Check the accuracy of the model on the test data
accuracy = labels_and_preds.filter(lambda x: x[0] == x[1]).count() / float(test_samples.count())
print("Model accuracy : {:.2f}".format(accuracy))
```

在 PySpark 中， predict 和 predictAll 是用于对模型进行预测的两种方法。

predict 是 MLlib 中的方法，用于对单个数据点进行预测，返回预测标签值。

predictAll 是 ML 中的方法，用于对多个数据点进行预测，返回一个 DataFrame，其中包含每个数据点的预测标签值。在使用 predictAll 时，需要传入一个包含数据点的 DataFrame，并将其传递给模型的 transform() 方法。

**需要注意的是，在 pyspark.ml 中，预测模型的方法名都是 transform()，而在 pyspark.mllib 中，方法名是 predict()。**