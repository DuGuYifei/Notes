# grid

[网格搜索](../../%E4%BA%BA%E5%B7%A5%E6%99%BA%E8%83%BD/AI%E7%AE%97%E6%B3%95/%E7%BD%91%E6%A0%BC%E6%90%9C%E7%B4%A2.md)

```python
# Import the tuning submodule
import pyspark.ml.tuning as tune

# Create the parameter grid
grid = tune.ParamGridBuilder()

# Add the hyperparameter
grid = grid.addGrid(lr.regParam, np.arange(0, .1, .01))
grid = grid.addGrid(lr.elasticNetParam, [0, 1])

# Build the grid
grid = grid.build()
```