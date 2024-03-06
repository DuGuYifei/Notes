# TextClassification

## select the data

```python
df_true = df.where("endword in ('she','he','hers','his','her',him')").withColumn('label',lit(1))

df_false = df.where("endword not in ('she','he','hers','his','her',him')").withColumn('label',lit(0))
```

## combining the positive and negative data

```python
df_examples = df_true.union(df_false)
```

## split the data into training and evaluation sets

```python
df_train, df_eval = df_examples.randomSplit([0.60, 0.40], seed=42)
```

## training

```python
from pyspark.ml.classification import LogisticRegression

logistic = LogisticRegression(maxIter=50, regParam=0.6, elasticNetParam=0.3)

model = logistic.fit(df_train)
print("Training iterations: ", model.summary.totalIterations)
```


## Predicting and evaluating

### applying the model to the evaluation data

```python
predicted = df_trained.transform(df_test)
```
* prediction column: double (一定是double)
* probability column: vector of length 2 (两个数字在[0,1]之间，和为1)
  * 第一个数字是false的概率
  * 第二个数字是true的概率
  * 默认转换概率使用0.5作为阈值

```python
x = predicted.first
print("Right!" if x.label == int(x.prediction) else "Wrong!")
```

### evaluating the model
**AUC: Area Under Curve**:
ROC曲线下的面积

```python
model_stats = model.evaluate(df_eval)
type(model_stats) # pyspark.ml.classification.BinaryLogisticRegressionSummary
print("\nPerformance: %.2f" % model_stats.areaUnderROC)
```
