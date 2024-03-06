# describe基础统计

```python
# Create a temporary view of fifa_df
fifa_df.createOrReplaceTempView('fifa_df_table')

# Construct the "query"
query = '''SELECT Age FROM fifa_df_table WHERE Nationality == "Germany"'''

# Apply the SQL "query"
fifa_df_germany_age = spark.sql(query)

# Generate basic statistics
fifa_df_germany_age.describe().show()
```

```
<script.py> output:
    +-------+-----------------+
    |summary|              Age|
    +-------+-----------------+
    |  count|             1140|
    |   mean|24.20263157894737|
    | stddev|4.197096712293756|
    |    min|               16|
    |    max|               36|
    +-------+-----------------+
```