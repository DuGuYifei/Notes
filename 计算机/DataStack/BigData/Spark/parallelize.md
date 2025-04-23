# parallelize

Load the list into Spark using Spark Context's parallelize method

Create an RDD 

sc is the Spark Context

```python
# Create a Python list of numbers from 1 to 100 
numb = range(1, 100)

# Load the list into PySpark  
spark_data = sc.parallelize(numb)
```