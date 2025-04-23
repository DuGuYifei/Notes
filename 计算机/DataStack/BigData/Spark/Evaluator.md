# Evaluator
验证用的：
比如areaUnderROC（AUC）: ROC（receiver operating curve）曲线是一种用于二分类问题的可视化工具。ROC曲线是真阳性率（TPR）与假阳性率（FPR）的函数。TPR是真阳性的比例，FPR是假阳性的比例。ROC曲线是在不同的阈值下绘制的。

AUC 越接近一 (1)，模型越好

```python
# Import the evaluation submodule
import pyspark.ml.evaluation as evals

# Create a BinaryClassificationEvaluator
evaluator = evals.BinaryClassificationEvaluator(metricName="areaUnderROC")
```
