# 过时的pyspark_mllib

## 过时
pyspark.mllib是一个过时的Spark ML库，由于设计限制和可扩展性问题，已经被新的Spark ML库`pyspark.ml`所取代。pyspark.mllib包含了一些经典的机器学习算法，例如线性回归、逻辑回归、朴素贝叶斯、决策树、随机森林、聚类等等。不过，由于已经不再更新和维护，建议使用pyspark.ml中的机器学习库进行开发和实验。

## import
```python
# Import the library for ALS
from pyspark.mllib.recommendation import ALS

# Import the library for Logistic Regression
from pyspark.mllib.classification import LogisticRegressionWithLBFGS

# Import the library for Kmeans
from pyspark.mllib.clustering import KMeans
```

## 数据准备
```python
# Load the data into RDD
data = sc.textFile(file_path)

# Split the RDD 
ratings = data.map(lambda l: l.split(','))

# Transform the ratings RDD 
ratings_final = ratings.map(lambda line: Rating(int(line[0]), int(line[1]), float(line[2])))

# Split the data into training and test
training_data, test_data = ratings_final.randomSplit([0.8, 0.2])
```

## training and prediction

```python
# Create the ALS model on the training data
model = ALS.train(training_data, rank=10, iterations=10)

# Drop the ratings column 
testdata_no_rating = test_data.map(lambda p: (p[0], p[1]))

# Predict the model  
predictions = model.predictAll(testdata_no_rating)

# Return the first 2 rows of the RDD
predictions.show(2)
```

## evaluate by MSE

```python
# Prepare ratings data
rates = ratings_final.map(lambda r: ((r[0], r[1]), r[2]))

# Prepare predictions data
preds = predictions.map(lambda r: ((r[0], r[1]), r[2]))

# Join the ratings data with predictions data
rates_and_preds = rates.join(preds)
# Calculate and print MSE
MSE = rates_and_preds.map(lambda r: (r[1][0] - r[1][1])**2).mean()
print("Mean Squared Error of the model for the test data = {:.2f}".format(MSE))
```

注意这里的join返回的是`[(r[0],r[1]),(rating0, rating1)]`