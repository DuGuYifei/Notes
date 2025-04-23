# WhenOtherwise

```python
import pyspark.sql.functions as F
voter_df = voter_df.withColumn('random_val',
                               F.when(voter_df.TITLE == 'Councilmember', F.rand()))


voter_df = voter_df.withColumn('random_val',
                               when(voter_df.TITLE == 'Councilmember', F.rand())
                               .when(voter_df.TITLE == 'Mayor', 2)
                               .otherwise(0))

```


