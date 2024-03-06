# 数据类型_cast

Spark model只处理numeric类型

所以string之类的需要cast来转换

通过使用cast函数，您可以将数据列从一种数据类型转换为另一种数据类型，例如将字符串转换为整数。

```python
from pyspark.sql.types import IntegerType
df = df.withColumn("age", df["age"].cast(IntegerType()))

# 或者使用字符串参数
df = df.withColumn("age", df["age"].cast("integer"))

## integer/int
## double
```