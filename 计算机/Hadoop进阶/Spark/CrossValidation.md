# CrossValidation

## 概念
[词汇收集](../../%E4%BA%BA%E5%B7%A5%E6%99%BA%E8%83%BD/%E8%AF%8D%E6%B1%87%E6%94%B6%E9%9B%86.md#交叉验证-cross-validation)

使用交叉验证来选择超参数，方法是为两个超参数 elasticNetParam 和 regParam 创建可能的值对网格，并使用交叉验证错误来比较所有不同的模型，以便您可以选择最佳模型！

## Evaluator
[Evaluator](Evaluator.md)

## grid
[grid](grid.md)

## 创建validator
lr见[Logistic Regression](Spark_LogisticRegression.md)

```python
# Create the CrossValidator
cv = tune.CrossValidator(estimator=lr,
               estimatorParamMaps=grid,
               evaluator=evaluator
               )
```
