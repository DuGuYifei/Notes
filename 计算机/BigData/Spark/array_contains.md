# array_contains

array_contains()	判断array中是否包含某个元素

```PYTHON
from pyspark.sql.functions import array_contains
df.where(array_contains('word array', 'the')).show(5, truncate=30)
```