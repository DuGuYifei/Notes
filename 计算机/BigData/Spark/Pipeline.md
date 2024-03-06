# Pipeline

Pipeline是`pyspark.ml`模块中的一个类，它可以`将所有已经创建的Estimator和Transformer组合`起来。这样，您就可以将相同的建模过程重复使用，将其包装在一个简单的对象中。

```python
# Import Pipeline
from pyspark.ml import Pipeline

# Make the pipeline
flights_pipe = Pipeline(stages=[dest_indexer, dest_encoder, carr_indexer, carr_encoder, vec_assembler])
```

stages 应该是一个列表，其中包含您希望数据在管道中经过的所有阶段。