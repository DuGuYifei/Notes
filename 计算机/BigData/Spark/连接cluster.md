# 连接cluster

## SparkContext类
```python
conf = SparkConf().set("spark.python.profile", "true")
sc = SparkContext('local', 'test', conf=conf, profiler_cls=MyCustomProfiler)

# Verify SparkContext
print(sc)

# Print Spark version
print(sc.version)

<script.py> output:
    <SparkContext master=local[*] appName=pyspark-shell>
    3.2.0
```

## SparkConf()属性
[pyspark package &mdash; PySpark 2.1.0 documentation](https://spark.apache.org/docs/2.1.0/api/python/pyspark.html)