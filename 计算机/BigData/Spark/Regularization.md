# Regularization


本课程介绍了一种更加复杂的回归模型——`正则化回归`，它可以有效地选择最有用的特征，从而创建一个具有最少预测变量的简化模型。

在回归模型中，每个特征都会有一个系数，这些系数量化了相应特征的影响。当数据集具有较少的列和许多行时，这种方法效果良好，因为只需要计算少量系数，并且有足够的数据。

然而，当数据集具有许多列和较少行时，情况就变得更加困难。此时需要计算大量系数的值，但数据较少。即使能够为所有系数计算出值，得到的模型也会非常复杂且难以解释。理想情况下，希望创建一个简洁的模型，即只包含所需的最小数量的预测变量。这样的模型应该尽可能简单，同时能够进行稳健的预测。

为了选择最佳的预测变量子集，可以使用各种方法进行"特征选择"。本课程介绍的一种方法是"惩罚回归"，即在损失函数中添加一个额外的"正则化"项或"收缩"项。正则化项与模型系数有关，而不是依赖于数据。

正则化项有两种标准形式。Lasso回归使用与系数的绝对值成比例的项，而岭回归使用系数的平方。这个额外项惩罚具有过多系数的模型。Lasso和岭回归之间有微妙的区别。两者都会缩小不重要预测变量的系数，但岭回归会使这些系数接近于零，而Lasso回归会将它们强制置零。还可以同时使用Lasso和岭回归。正则化的强度由一个参数决定，通常用希腊字母lambda表示。当lambda = 0时，没有正则化，当lambda很大时，正则化完全主导。理想情况下，应选择介于这两个极端之间的lambda值。

通过对车辆数据进行实际案例分析，可以更好地理解特征选择和正则化的概念。在回归模型中，通过选择合适的lambda值，可以得到只包含重要预测变量的简化模型，从而在保持性能的同时降低复杂性。

在实际应用中，可以将正则化应用于飞行时间模型，以进一步改善预测结果。

## 普通回归
```python
from pyspark.ml.regression import LinearRegression
from pyspark.ml.evaluation import RegressionEvaluator

# Fit linear regression model to training data
regression = LinearRegression(labelCol='duration').fit(flights_train)

# Make predictions on testing data
predictions = regression.transform(flights_test)

# Calculate the RMSE on testing data
rmse = RegressionEvaluator(labelCol='duration').evaluate(predictions)
print("The test RMSE is", rmse)

# Look at the model coefficients
coeffs = regression.coefficients
print(coeffs)
```

## 正则回归
```python
from pyspark.ml.regression import LinearRegression
from pyspark.ml.evaluation import RegressionEvaluator

# Fit Lasso model (λ = 1, α = 1) to training data
regression = LinearRegression(labelCol='duration', regParam=1, elasticNetParam=1).fit(flights_train)

# Calculate the RMSE on testing data
rmse = RegressionEvaluator(labelCol='duration').evaluate(regression.transform(flights_test))
print("The test RMSE is", rmse)

# Look at the model coefficients
coeffs = regression.coefficients
print(coeffs)

# Number of zero coefficients
zero_coeff = sum([beta == 0 for beta in regression.coefficients])
print("Number of coefficients equal to 0:", zero_coeff)
```